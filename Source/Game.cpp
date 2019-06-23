//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#include "Game.h"

bool Game::Initialize(SDL_Surface* screenSurface) {

    GameObject* ball = CreateObject((int)ObjectIDs::Paddle_Left);
    GameObject* rPaddle = CreateObject((int)ObjectIDs::Paddle_Right);
    GameObject* lPaddle = CreateObject((int)ObjectIDs::Ball);

    ball->SetPosition(WIDTH / 2, HEIGHT / 2);
    ball->SetSize(1, 1);

    lPaddle->SetPosition(6, HEIGHT / 2);
    lPaddle->SetSize(2, 8);
    rPaddle->SetPosition(WIDTH - 6, HEIGHT / 2);
    rPaddle->SetSize(2, 8);

    renderSurf = SDL_CreateRGBSurfaceWithFormat(screenSurface->flags, WIDTH, HEIGHT, 32, screenSurface->format->format);
    if(renderSurf == NULL) {
        std::cerr << "Failed to create render surface!" << SDL_GetError() << std::endl;
        return false;
    }

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

void Game::HandleSDLEvent(SDL_Event& ev) {
    if(ev.type == SDL_KEYDOWN) {
    }
}

void Game::Update() {

//    GameObject* ball = gObjects[ObjectIDs::Ball];
//    GameObject* lPaddle = gObjects[ObjectIDs::Paddle_Left];
//    GameObject* rPaddle = gObjects[ObjectIDs::Paddle_Right];

//    if(ball->X() < 0) {
        //P2 scored
//    }
//    else if(ball->X() > WIDTH) {
        //P1 scored
//    }

    //Check collisions
        //Left paddle
        //Right paddle
        //Screen edges

    //Update positions
}

void Game::Render(SDL_Surface* surface) {
    SDL_FillRect(renderSurf, NULL, SDL_MapRGB(renderSurf->format, 0x00, 0x00, 0x00));

    Uint32 white = SDL_MapRGB(renderSurf->format, 0xFF, 0xFF, 0xFF);
    for(auto it = gObjects.begin(); it != gObjects.end(); it++) {

        GameObject* obj = it->second;

        for(int x = obj->Left(); x < obj->Right(); x++) {
            for(int y = obj->Top(); y < obj->Bottom(); y++) {
                SetPixel(x, y, white);
            }
        }
    }

    SDL_BlitScaled(renderSurf, NULL, surface, NULL);
}

void Game::SetPixel(int x, int y, Uint32 color) {
    Uint8 *pixel = (Uint8 *)renderSurf->pixels + y * renderSurf->pitch + x * 4;
    *(Uint32*)pixel = color;
}
