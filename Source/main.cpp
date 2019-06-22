#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* g_window = NULL;
SDL_Surface* g_screenSurface = NULL;
bool g_gameOver = false;

bool Initialize();

void Shutdown();

void HandleEvents();

int main() {

    if(!Initialize()) {
        return -1;
    }

    while(!g_gameOver) {

        HandleEvents();
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

    return true;
}

void Shutdown() {

    SDL_DestroyWindow(g_window);

    SDL_Quit();
}

void HandleEvents() {
    static SDL_Event ev;

    while(SDL_PollEvent(&ev) != 0) {
        if(ev.type == SDL_QUIT) {
            g_gameOver = true;
        }
    }
}