#pragma once

#include "Player.h"
#include <vector>
#include <random>

class Game {
    public:
        Game();
        int  run();
        void addMessage(const std::string& msg);
        void setTurn(const std::string& newTurn);
        int  getSeed(); 
        std::mt19937& getGenerator();

    private:
        std::vector<std::string> msgs;
        std::string turn;
        int seed; // Seed
        std::mt19937 gen;
        // Player player;
        // int lives;
        // int score;

        // void InitGame();
        // void UpdateGame();
        // void DrawGame();
        // void UnloadGame();
};