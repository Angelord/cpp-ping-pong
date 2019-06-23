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
    void SetPosition(int x, int y) { position.Set(x, y); }
    void Move(const Vector2& dir) { position = position + dir; }
    void AddVelocity(const Vector2& dir) { velocity = velocity + dir; }
    void ClearVelocity() { velocity.Set(0.0f, 0.0f); }

    int HalfWidth() const { return halfWidth; }
    void SetHalfWidth(int value) { halfWidth = value; }
    int HalfHeight() const { return halfHeight; }
    void SetHalfHeight(int value) { halfHeight = value; }
    void SetSize(int halfWidth, int halfHeight) { this->halfWidth = halfWidth; this->halfHeight = halfHeight; }
};


#endif //CPP_PING_PONG_GAMEOBJECT_H
