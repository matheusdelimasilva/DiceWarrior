#pragma once

#include "Player.h"
#include "Level.h"
#include <vector>
#include <random>

class Game {
    public:
        Game();
        ~Game();
        int  run();
        void addMessage(const std::string& msg);
        void setTurn(const std::string& newTurn);
        int  getSeed(); 
        void printStats(std::vector<Player*> players);
        std::mt19937& getGenerator();
        std::vector<Player*>& getPlayers(); // returns a reference to players
        std::vector<Player*>& getEnemies(); // returns a reference to enemies
        Level* getCurrLevel();              // returns a reference to curr level 

    private:
        std::vector<std::string> msgs;
        std::string              turn;
        int                      seed;    // Seed
        std::mt19937             gen;
        std::vector<Player*>     players; // pointers to players
        Level*                   currLvl; // pointer to the current level object 
        
        // Player player;
        // int lives;
        // int score;

        // void InitGame();
        // void UpdateGame();
        // void DrawGame();
        // void UnloadGame();
};