//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#ifndef CPP_PING_PONG_POINT_H
#define CPP_PING_PONG_POINT_H

struct Vector2 {

    float x;
    float y;

    explicit Vector2() : x(0), y(0) { }

    Vector2(float x, float y) : x(x), y(y) {}

    void Set(float x, float y) { this->x = x; this->y = y; }

    float Magnitude() const {
        return sqrt(x * x + y * y);
    }

    float MagnitudeSqr() const {
        return x * x + y * y;
    }

    void Normalize() {
        float mag = Magnitude();
        x /= mag;
        y /= mag;
    }

    Vector2 operator/(float rhs) {
        return {x / rhs, y / rhs};
    }

    Vector2 operator*(float rhs) {
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
