#include <iostream>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "ERROR::Failed to initialize SDL!" << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        std::cerr << "ERROR::Failed to create window!" << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}