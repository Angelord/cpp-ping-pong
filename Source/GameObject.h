//
// Created by Angel Paunov Georgiev on 2019-06-22.
//

#ifndef CPP_PING_PONG_GAMEOBJECT_H
#define CPP_PING_PONG_GAMEOBJECT_H

#include "Core.h"

class GameObject {

    int id;
    Vector2 position;
    Vector2 velocity;
    int halfWidth;
    int halfHeight;

public:

    GameObject(int id) : id(id) { }

    int ID() const { return id; }

    int Top() const { return Y() - halfHeight; }
    int Left() const { return X() - halfWidth; }
    int Bottom() const { return Y() + halfHeight; }
    int Right() const { return X() + halfWidth; }
    int X() const { return (int)roundf(position.x); }
    int Y() const { return (int)roundf(position.y); }
    void SetX(float val) { position.x = val; }
    void SetY(float val) { position.y = val; }
    Vector2 Position() const { return position; }
    void SetPosition(const Vector2& position) { this->position = position; }
    void SetPosition(int x, int y) { position.Set((float)x, (float)y); }
    Vector2 Velocity() const { return velocity; }
    void SetVelocity(const Vector2& velocity) { this->velocity = velocity; }


    int HalfWidth() const { return halfWidth; }
    void SetHalfWidth(int value) { halfWidth = value; }
    int HalfHeight() const { return halfHeight; }
    void SetHalfHeight(int value) { halfHeight = value; }
    void SetSize(int halfWidth, int halfHeight) { this->halfWidth = halfWidth; this->halfHeight = halfHeight; }
};


#endif //CPP_PING_PONG_GAMEOBJECT_H
