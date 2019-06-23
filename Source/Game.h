//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#ifndef CPP_PING_PONG_LOGIC_H
#define CPP_PING_PONG_LOGIC_H

#include "GameObject.h"

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

    bool over = false;
    std::map<int, GameObject*> gObjects;
    SDL_Surface* renderSurf = NULL;
    float curBallSpeed = SPEED_BALL;
    int scoreLeft = 0;
    int scoreRight = 0;

public:

    Game() : gObjects() { }

    ~Game();

    bool Initialize(SDL_Surface* screenSurface);

    void HandleSDLEvent(const SDL_Event& ev);

    void Update();

    void Render(SDL_Surface* surface);

private:

    GameObject* CreateObject(int id);

    void OnScore(Side side);

    void ResetBall();

    void SetPixel(int x, int y, Uint32 color);
};

#endif //CPP_PING_PONG_LOGIC_H
