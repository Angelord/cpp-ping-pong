#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;
const int TICKS_PER_FRAME = 1000 / FPS;

SDL_Window* g_window = NULL;
SDL_Surface* g_screenSurface = NULL;
Game* g_game = NULL;
bool g_quit = false;

bool Initialize();

void Shutdown();

void HandleEvents();

int main() {

    if(!Initialize()) {
        return -1;
    }

    Timer frameCapTimer;

    while(!g_quit) {

        frameCapTimer.Start();

        HandleEvents();

        g_game->Update();

        g_game->Render(g_screenSurface);

        SDL_UpdateWindowSurface(g_window);

        unsigned frameTicks = frameCapTimer.GetTicks();
        if(frameTicks < TICKS_PER_FRAME) {
            SDL_Delay(TICKS_PER_FRAME - frameTicks);
        }
    }

    Shutdown();

    return 0;
}

bool Initialize() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "ERROR::Failed to initialize SDL!" << SDL_GetError() << std::endl;
        return false;
    }

    g_window = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL) {
        std::cerr << "ERROR::Failed to create window!" << SDL_GetError() << std::endl;
        return false;
    }

    g_screenSurface = SDL_GetWindowSurface(g_window);

    g_game = new Game;
    if(!g_game->Initialize(g_screenSurface)) {
        std::cerr << "ERROR::Failed to initialize Game!" << std::endl;
        return false;
    }

    return true;
}

void Shutdown() {

    delete g_game;

    SDL_DestroyWindow(g_window);

    SDL_Quit();
}

void HandleEvents() {
    static SDL_Event ev;

    while(SDL_PollEvent(&ev) != 0) {
        if(ev.type == SDL_QUIT) {
            g_quit = true;
        }
        else {
            g_game->HandleSDLEvent(ev);
        }
    }
}