//
// Created by Angel Paunov Georgiev on 2019-06-23.
//

#include "Timer.h"
#include "Core.h"

Timer::Timer() :
    started(false),
    paused(false),
    startTicks(0),
    pausedTicks(0) {
}

void Timer::Start() {
    started = true;
    paused = false;

    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::Stop() {
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::Pause() {
    if(started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::Unpause() {
    if(started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

unsigned Timer::GetTicks() {

    if(!started) {
        return 0;
    }

    if(paused) {
        return pausedTicks;
    }

    return SDL_GetTicks() - startTicks;
}