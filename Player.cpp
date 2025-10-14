#include "Player.h"

Player::Player()
{
    position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() - 100 };
    speed = 5.0f;
    texture = LoadTexture("rocket.png");
    scale = 0.1f;
}

void Player::Update()
{
    if (IsKeyDown(KEY_LEFT)) position.x -= speed;
    if (IsKeyDown(KEY_RIGHT)) position.x += speed;

    if (position.x < 0) position.x = 0;
    if (position.x > GetScreenWidth() - texture.width * scale) position.x = GetScreenWidth() - texture.width * scale;
}

void Player::Draw()
{
    DrawTextureEx(texture, position, 0.0f, scale, WHITE);
}

Rectangle Player::getRect()
{
    return { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
}
