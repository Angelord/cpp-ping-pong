//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#include "Game.h"

const Vector2 Game::BALL_POS_CENTER(WIDTH / 2, HEIGHT / 2);
const Vector2 Game::BALL_POS_LEFT(8, HEIGHT / 2);
const Vector2 Game::BALL_POS_RIGHT(WIDTH - 8, HEIGHT / 2);

bool Game::Initialize(SDL_Surface* screenSurface) {

    GameObject* ball = CreateObject((int)ObjectIDs::Ball);
    GameObject* rPaddle = CreateObject((int)ObjectIDs::Paddle_Right);
    GameObject* lPaddle = CreateObject((int)ObjectIDs::Paddle_Left);

    ball->SetSize(2, 2);

    lPaddle->SetSize(2, 8);
    rPaddle->SetSize(2, 8);
    lPaddle->SetPosition(6, HEIGHT / 2);
    rPaddle->SetPosition(WIDTH - 6, HEIGHT / 2);

    renderSurf = SDL_CreateRGBSurfaceWithFormat(screenSurface->flags, WIDTH, HEIGHT + MARGIN_HEIGHT, 32, screenSurface->format->format);
    if(renderSurf == NULL) {
        std::cerr << "Failed to create render surface!" << SDL_GetError() << std::endl;
        return false;
    }

    ResetBall(BALL_POS_LEFT);
    LaunchBall(Vector2::RIGHT);

    return true;
}

Game::~Game() {
    for(auto& gObject : gObjects) {
        delete (gObject.second);
    }
    gObjects.clear();
}

GameObject* Game::CreateObject(int id) {
    GameObject* obj = new GameObject(id);
    gObjects[id] = obj;
    return obj;
}

void Game::HandleSDLEvent(const SDL_Event& ev) {
    if(ev.type == SDL_KEYDOWN) {
        SDL_Keycode key = ev.key.keysym.sym;
        if(key == SDLK_RETURN || key == SDLK_SPACE) {
            over = false;
            scoreLeft = 0;
            scoreRight = 0;
            LaunchBall(Vector2::RIGHT);
        }
    }
}

void Game::Update() {

    if(over) { return; }

    GameObject* lPaddle = gObjects[(int)Paddle_Left];
    GameObject* rPaddle = gObjects[(int)Paddle_Right];
    GameObject* ball = gObjects[(int)Ball];

    // Handle input
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if(keyState[SDL_SCANCODE_UP] && rPaddle->Top() > 0) {
        gObjects[(int)Paddle_Right]->SetVelocity(Vector2::UP * SPEED_PADDLE);
    }
    else if(keyState[SDL_SCANCODE_DOWN] && rPaddle->Bottom() < HEIGHT) {
        gObjects[(int)Paddle_Right]->SetVelocity(Vector2::DOWN * SPEED_PADDLE);
    }

    if(keyState[SDL_SCANCODE_W] && lPaddle->Top() > 0) {
        gObjects[(int)Paddle_Left]->SetVelocity(Vector2::UP * SPEED_PADDLE);
    }
    else if(keyState[SDL_SCANCODE_S] && lPaddle->Bottom() < HEIGHT) {
        gObjects[(int)Paddle_Left]->SetVelocity(Vector2::DOWN * SPEED_PADDLE);
    }

    // Handle wall collision
    if(ball->Top() < 0 || ball->Bottom() > HEIGHT) {
        ball->SetVelocity(Vector2(ball->Velocity().x, -ball->Velocity().y));    // Change y direction
        beeper.Beep(SOUND_HIT_HZ, SOUND_HIT_DURATION);
    }

    // Handle paddle collision
    bool hit = false;
    GameObject* hitPaddle = NULL;
    if(ball->Velocity().x < 0.0f
    && ball->Left() < lPaddle->Right()
    && ball->Right() > lPaddle->Left()
    && ball->Bottom() > lPaddle->Top()
    && ball->Top() < lPaddle->Bottom()) {
        hit = true;
        hitPaddle = lPaddle;
    }
    else if(ball->Velocity().x > 0.0f
    && ball->Right() > rPaddle->Left()
    && ball->Left() < rPaddle->Right()
    && ball->Bottom() > rPaddle->Top()
    && ball->Top() < rPaddle->Bottom()) {
        hit = true;
        hitPaddle = rPaddle;
    }

    if(hit) {
        curBallSpeed += SPEED_INCREMENT;
        Vector2 ballVel = ball->Velocity();
        ballVel.x = -sgn(ballVel.x);
        ballVel.y += rnDis(rnGen) / 4.0f;
        ballVel.Normalize();
        ball->SetVelocity(ballVel * curBallSpeed);
        beeper.Beep(SOUND_HIT_HZ, SOUND_HIT_DURATION);
    }

    // Check for scoring
    if(ball->Left() < 0) {
        OnScore(Right);
        return;
    }
    else if(ball->Right() > WIDTH) {
        OnScore(Left);
        return;
    }

    // Resolve movement
    for(auto& gObj : gObjects) {
        GameObject* gameObject = gObj.second;
        gameObject->SetPosition(gameObject->Position() + gameObject->Velocity());
    }


    lPaddle->SetVelocity(Vector2::ZERO);
    rPaddle->SetVelocity(Vector2::ZERO);
}

void Game::OnScore(Side side) {

    side == Left ? ++scoreLeft : ++scoreRight;

    if(scoreLeft == SCORE_MAX || scoreRight == SCORE_MAX) {
        over = true;
        gObjects[(int)Paddle_Left]->SetY(HEIGHT / 2);
        gObjects[(int)Paddle_Right]->SetY(HEIGHT / 2);
        ResetBall(BALL_POS_CENTER);
        return;
    }

    ResetBall(side == Left ? BALL_POS_LEFT : BALL_POS_RIGHT);
    LaunchBall(side == Left ? Vector2::RIGHT : Vector2::LEFT);
}

void Game::ResetBall(const Vector2& pos) {

    GameObject* ball = gObjects[(int)Ball];

    curBallSpeed = SPEED_BALL;
    ball->SetPosition(pos);
}

void Game::LaunchBall(const Vector2& dir) {
    Vector2 vel = dir;
    vel.y = rnDis(rnGen);
    gObjects[(int)Ball]->SetVelocity(vel);
}

void Game::Render(SDL_Surface* surface) {

    Uint32 black = SDL_MapRGB(renderSurf->format, 0x00, 0x00, 0x00);
    Uint32 white = SDL_MapRGB(renderSurf->format, 0xFF, 0xFF, 0xFF);

    SDL_FillRect(renderSurf, NULL, black);

    for(auto it = gObjects.begin(); it != gObjects.end(); it++) {

        GameObject* obj = it->second;

        for(int x = obj->Left(); x < obj->Right(); x++) {
            for(int y = obj->Top(); y < obj->Bottom(); y++) {
                SetPixel(x, y, white);
            }
        }
    }

    for(int x = 0; x < WIDTH; x++) {
        for(int y = HEIGHT; y < HEIGHT + MARGIN_HEIGHT; y++) {
            SetPixel(x, y, white);
        }
    }

    for(int l = 0; l < scoreLeft; l++) {
        SetPixel(10 + l * 4, HEIGHT + MARGIN_HEIGHT / 2, black);
    }

    for(int r = 0; r < scoreRight; r++) {
        SetPixel(WIDTH - (10 + r * 4), HEIGHT + MARGIN_HEIGHT / 2, black);
    }

    SDL_BlitScaled(renderSurf, NULL, surface, NULL);
}

void Game::SetPixel(int x, int y, Uint32 color) {
    Uint8 *pixel = (Uint8 *)renderSurf->pixels + y * renderSurf->pitch + x * 4;
    *(Uint32*)pixel = color;
}
