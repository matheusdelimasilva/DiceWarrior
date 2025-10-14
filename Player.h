#pragma once

//#include "raylib.h"
#include <string> 

class Player
{
public:
    std::string name; 
    int roll = 0; 
    int attack = 0; 
    int defense = 0;
    int health = 50;

    Player();
private:
    
};