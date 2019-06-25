//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#ifndef CPP_PING_PONG_LOGIC_H
#define CPP_PING_PONG_LOGIC_H

#include "GameObject.h"
#include "Beeper.h"
#include <random>

enum ObjectIDs {
    Paddle_Left,
    Paddle_Right,
    Ball
};

enum Side {
    Left,
    Right
};

class Game {

    static constexpr int WIDTH = 128;
    static constexpr int HEIGHT = 84;
    static constexpr int MARGIN_HEIGHT = 12;
    static constexpr float SPEED_BALL = 1.0f;
    static constexpr float SPEED_INCREMENT = 0.1f;  //How much the ball's speed increases when hit
    static constexpr float SPEED_PADDLE = 1.0f;
    static constexpr int SCORE_MAX = 6;
    static constexpr double SOUND_HIT_HZ = 350.0;
    static constexpr int SOUND_HIT_DURATION = 80;

    static const Vector2 BALL_POS_CENTER;
    static const Vector2 BALL_POS_LEFT;
    static const Vector2 BALL_POS_RIGHT;

    bool over = false;
    std::map<int, GameObject*> gObjects;
    SDL_Surface* renderSurf = NULL;
    float curBallSpeed = SPEED_BALL;
    int scoreLeft = 0;
    int scoreRight = 0;
    std::mt19937 rnGen;
    std::uniform_real_distribution<float> rnDis;
    Beeper beeper;

  public:

    Game() : gObjects(), rnDis(-1.0f, 1.0f) { }

    ~Game();

    bool Initialize(SDL_Surface* screenSurface);

    void HandleSDLEvent(const SDL_Event& ev);

    void Update();

    void Render(SDL_Surface* surface);

private:

    GameObject* CreateObject(int id);

    void OnScore(Side side);

    void ResetBall(const Vector2& pos);

    void LaunchBall(const Vector2& dir);

    void SetPixel(int x, int y, Uint32 color);
};

#endif //CPP_PING_PONG_LOGIC_H
