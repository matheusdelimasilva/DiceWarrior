#include "Player.h"
#include "Game.h"
#include <random> 
#include <iostream>
#include <fmt/core.h>


// Constructor 
Player::Player(const std::string& name, Game* game, int health) {
    this->name        = name; 
    this->gameContext = game; 
    this->health      = health;
    this->roll        = 0; 
    this->attack      = 0; 
    this->defense     = 0;
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
            this->gameContext->addMessage(fmt::format("{} rolled 1, lost turn!", this->name));
            this->gameContext->setTurn("enemy"); // Player loses its turn 
        }
        // Double damage
        else if (this->roll == 6){
            this->gameContext->addMessage(fmt::format("{} rolled 6, double damage!", this->name));
            this->attack = this->attack * 2; 
        }
        // Normal roll
        else {
            this->gameContext->addMessage(fmt::format("{} rolled: {}", this->name, this->roll));
            this->attack += this->roll; 
        }
    }
    // Attack
    else if (input_vec[0] == "A") {
        // Show options to user
        std::cout << "Select target:"; 
        int i = 0;
        std::vector<Player*>& playerList = this->gameContext->getEnemies();
        for (const auto& player : playerList) {
            std::cout << fmt::format(" [{}] {}", i, player->name); 
            i++; 
        }
        std::cout << std::endl; 

        // Requests input 
        std::string target_str; 
        std::getline(std::cin, target_str);

        // Transform input into a pointer to Player target
        Player* target = playerList[std::stoi(target_str)];

        this->gameContext->addMessage(
            fmt::format("Attacked {}: -{}", target->name, this->attack));
        target->health = target->health - (this->attack - target->defense);
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
            this->gameContext->addMessage(fmt::format("{} rolled 1, lost turn!", this->name));
            this->gameContext->setTurn("player"); // Player loses its turn 
            return; 
        }

        // Double damage
        else if (this->roll == 6){
            this->gameContext->addMessage(fmt::format("{} rolled 6, double damage!", this->name));
            this->attack = this->attack * 2; 
        }
        // Normal roll
        else {
            this->gameContext->addMessage(fmt::format("{} rolled: {}", this->name, this->roll));
            this->attack += this->roll; 
        }

        // 50% chance of finishing turn  
        is_turn = rollDice(1, 100) >= 50;
    }

    std::vector<Player*>& playerList = this->gameContext->getPlayers();
    // select random target 
    Player* target = playerList[this->rollDice(0, playerList.size()-1)]; 
    this->gameContext->addMessage(
        fmt::format("Attacked {}: -{}", target->name, this->attack));
    target->health = target->health - (this->attack - target->defense);
    this->attack = 0;
    this->gameContext->setTurn("player"); // Finished turn 
}

void Player::printStats() {
    std::cout << "| == " << this->name << " Stats == | " << this->attack << std::endl;
    std::cout << "| Attack: " << this->attack << std::endl;
    std::cout << "| Defense: " << this->defense << std::endl;
    std::cout << "| Health: " << this->health << std::endl;
}
