#pragma once

//#include "raylib.h"
#include <string> 
#include <vector>

class Game; // Forward declaration

class Player
{
public:
    std::string name; 
    int roll = 0; 
    int attack = 0; 
    int defense = 0;
    int health = 50;

    void run_turn(std::vector<std::string> input_vec); // Run turn with actions provided
    void run_turn();                                   // Run turn as an NPC
    int  rollDice(int min, int max);
    void printStats(); 

    Player(const std::string& name, Game* game);
private:
    Game* gameContext;
};