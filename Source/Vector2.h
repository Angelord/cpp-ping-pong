//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#ifndef CPP_PING_PONG_POINT_H
#define CPP_PING_PONG_POINT_H

#include <math.h>

struct Vector2 {

    static const Vector2 UP;
    static const Vector2 DOWN;
    static const Vector2 LEFT;
    static const Vector2 RIGHT;
    static const Vector2 ZERO;

    float x;
    float y;

    explicit Vector2() : x(0), y(0) { }

    Vector2(float x, float y) : x(x), y(y) {}

    void Set(float x, float y) { this->x = x; this->y = y; }

    void Normalize() {
        float mag = Magnitude();
        x /= mag;
        y /= mag;
    }

    float Magnitude() {
        return sqrt(x * x + y * y);
    }

    Vector2 operator/(float rhs) const {
        return {x / rhs, y / rhs};
    }

    Vector2 operator*(float rhs) const {
        return {x * rhs, y * rhs};
    }
};

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

#endif //CPP_PING_PONG_POINT_H
