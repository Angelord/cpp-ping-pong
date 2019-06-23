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

class Game {

    static constexpr int WIDTH = 128;
    static constexpr int HEIGHT = 96;
    static constexpr float SPEED_BALL = 1.4f;
    static constexpr float SPEED_PADDLE = 1.0f;

    bool over = false;
    std::map<int, GameObject*> gObjects;
    SDL_Surface* renderSurf = NULL;

public:

    Game() : gObjects() { }

    ~Game();

    bool Initialize(SDL_Surface* screenSurface);

    void Update();

    void Render(SDL_Surface* surface);

    bool Over() const { return over; }

private:

    GameObject* CreateObject(int id);

    void Reset();

    void SetPixel(int x, int y, Uint32 color);
};

#endif //CPP_PING_PONG_LOGIC_H
