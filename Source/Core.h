//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#ifndef CPP_PING_PONG_CORE_H
#define CPP_PING_PONG_CORE_H

#include <map>
#include <string>
#include <SDL.h>
#include <iostream>
#include "Vector2.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

#endif //CPP_PING_PONG_CORE_H
