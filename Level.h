#pragma once

//#include "raylib.h"
#include <string> 
#include <vector>
#include "Player.h"

class Level; // Forward declaration

class Level {
public:
    std::vector<Player*>& getEnemies(); // returns a reference to enemies
    Level(int number, Game* game);
private:
    std::vector<Player*> enemies; // pointers to enemies
    int number; // Level 1, 2, ...
    Game* gameContext;
};