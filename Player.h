#pragma once

#include "raylib.h"

class Player
{
public:
    Player();
    void Update();
    void Draw();
    Rectangle getRect();

private:
    Vector2 position;
    float speed;
    Texture2D texture;
    float scale;
};