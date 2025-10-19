#include "Level.h"
#include "Player.h"
#include <string> 
#include <vector>


// Constructor 
Level::Level(int number, Game* game) {
    this->number      = number;
    this->gameContext = game;
    if (number == 1) {
        Player* enemy1 = new Player("Monster 1", game, 30);   // Enemy 
        Player* enemy2 = new Player("Monster 2", game, 25);    // Enemy 
        this->enemies  = { enemy1, enemy2 };
    }
}

std::vector<Player*>& Level::getEnemies() {
    return enemies;
}