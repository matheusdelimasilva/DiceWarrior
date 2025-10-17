#include "Player.h"
#include "Game.h"
#include <random> 
#include <iostream>
#include <format>

// Constructor 
Player::Player(const std::string& name, Game* game) {
    this->name        = name; 
    this->gameContext = game; 
}

int Player::rollDice(int min, int max) {
    std::uniform_int_distribution<> distrib(min, max); // Uniform integer dist
    int random_number = distrib(this->gameContext->getGenerator());
    return random_number;
}

// Runs when it's the players turn
void Player::run_turn(std::vector<std::string> input_vec) {
    // Roll 
    if (input_vec[0] == "R") {
        this->roll = this->rollDice(1,6);
        // Lose turn 
        if (this->roll == 1 ){
            this->attack = 0;
            this->gameContext->addMessage(std::format("{} rolled 1, lost turn!", this->name));
            this->gameContext->setTurn("enemy"); // Player loses its turn 
        }
        // Double damage
        else if (this->roll == 6){
            this->gameContext->addMessage(std::format("{} rolled 6, double damage!", this->name));
            this->attack = this->attack * 2; 
        }
        // Normal roll
        else {
            this->gameContext->addMessage(std::format("{} rolled: {}", this->name, this->roll));
            this->attack += this->roll; 
        }
    }
    // Attack
    else if (input_vec[0] == "A") {
        std::cout << "Attacked enemy: -" << this->attack << std::endl;
        this->attack = 0; 
        this->gameContext->setTurn("enemy"); // Finished turn 
    }
    else {
        std::cout << input_vec[0] << ": command not found" << std::endl;
    }
}


void Player::run_turn() {
    bool is_turn = true; 

    while (is_turn == true) {
        this->roll = this->rollDice(1, 6);

        if (this->roll == 1 ){
            this->attack = 0;
            this->gameContext->addMessage(std::format("{} rolled 1, lost turn!", this->name));
            is_turn = false; // Player loses its turn 
        }

        // Double damage
        else if (this->roll == 6){
            this->gameContext->addMessage(std::format("{} rolled 6, double damage!", this->name));
            this->attack = this->attack * 2; 
        }
        // Normal roll
        else {
            this->gameContext->addMessage(std::format("{} rolled: {}", this->name, this->roll));
            this->attack += this->roll; 
        }

        // 50% chance of finishing turn  
        is_turn = rollDice(1, 100) >= 50;
    }

    this->gameContext->setTurn("player");
}

void Player::printStats() {
    std::cout << "| == " << this->name << " Stats == | " << this->attack << std::endl;
    std::cout << "| Attack: " << this->attack << std::endl;
    std::cout << "| Defense: " << this->defense << std::endl;
    std::cout << "| Health: " << this->health << std::endl;
}
