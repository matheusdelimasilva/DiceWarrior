#include "Game.h"
//#include "raylib.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <iomanip> // setw 
#include <algorithm> // remove_if 
#include <chrono>  
#include <thread> 

// #include <unordered_set>

#define SCREEN_WIDTH 120

// Takes an input string and breaks it into a vector.
std::vector<std::string> tokenize(std::string input) {
    // Tokenize the input 
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void Game::printStats(std::vector<Player*> players) {
    //const int cardWidth = 22;
    const int cardsPerRow = 6;

    for (size_t i = 0; i < players.size(); i += cardsPerRow) {
        // Top border
        for (size_t j = i; j < i + cardsPerRow && j < players.size(); j++) {
            std::cout << " ╔════════════════════╗ ";
        }
        std::cout << "\n";

        // Name row
        for (size_t j = i; j < i + cardsPerRow && j < players.size(); j++) {
            std::string name = players[j]->name;
            if (name.length() > 18) name = name.substr(0, 15) + "...";
            std::cout << " ║ " << std::left << std::setw(18) << name << " ║ ";
        }
        std::cout << "\n";

        // Separator
        for (size_t j = i; j < i + cardsPerRow && j < players.size(); j++) {
            std::cout << " ╠════════════════════╣ ";
        }
        std::cout << "\n";

        // Health row
        for (size_t j = i; j < i + cardsPerRow && j < players.size(); j++) {
            std::cout << " ║ ❤️  HP: " << std::left << std::setw(12)
                << players[j]->health << "║ ";
        }
        std::cout << "\n";

        // Attack row
        for (size_t j = i; j < i + cardsPerRow && j < players.size(); j++) {
            std::cout << " ║ ⚔️  ATK: " << std::left << std::setw(11)
                << players[j]->attack << "║ ";
        }
        std::cout << "\n";

        // Defense row
        for (size_t j = i; j < i + cardsPerRow && j < players.size(); j++) {
            std::cout << " ║ 🛡️  DEF: " << std::left << std::setw(11)
                << players[j]->defense << "║ ";
        }
        std::cout << "\n";

        // Bottom border
        for (size_t j = i; j < i + cardsPerRow && j < players.size(); j++) {
            std::cout << " ╚════════════════════╝ ";
    }
        std::cout << "\n\n";
    }
}



// Repeats a char n times
void printRepeatChar(char c, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << c;
    }
}

void printMessage(std::vector<std::string>& msgs, bool center=false) {
    printRepeatChar('=', SCREEN_WIDTH); std::cout << std::endl;

    if (center == true) {
        for (const auto& msg : msgs) { 
            std::cout << "|"; 
            int half = (( SCREEN_WIDTH - msg.length() ) / 2) - 1; 
            printRepeatChar(' ', half); std::cout << msg; printRepeatChar(' ', half); 
            std::cout <<"|" << std::endl;
            printRepeatChar('=', SCREEN_WIDTH); std::cout << std::endl;
        }
    }
    else {
        for (const auto& msg : msgs) {
            //std::this_thread::sleep_for(std::chrono::milliseconds(800));
            std::cout << "| " << msg; 
            int padding = SCREEN_WIDTH - msg.length() - 4;
            printRepeatChar(' ', padding);
            std::cout << " |" << std::endl; 
        }
    }
    if (!msgs.empty()) {
        msgs.pop_back();
    }
    printRepeatChar('=', SCREEN_WIDTH); std::cout << std::endl;

}

void checkStats(std::vector<Player*>& players) {
    // Remove pointers from vector if health <= 0
    players.erase(
        std::remove_if(players.begin(), players.end(), 
            [](const Player* player) {
                return player->health <= 0;
            }
        ),
        players.end()
    );
}

void ClearTerminal() {
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

int Game::run() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf; // Flush after every std::cout / std:cerr
    std::string input;         // string containing user input 
    std::vector<std::string> input_vec; // Input break into tokens

    this->turn = "player"; // Player starts the round

    ClearTerminal();
    
    Player p      = Player( "Player", this, 50 );      // Player  
    
    this->players   = { &p };
    Level lvl       = Level(1, this); 
    this->currLvl   = &lvl;

    this->addMessage("Welcome!");

    while (true) {
        // Print a msg (if it exists)
        if (!msgs.empty()) {
            printMessage(msgs); 
        }
        printStats(players);
        printStats(lvl.getEnemies());
        std::cout << "Actions: " << std::endl;
        std::cout << "[R] Roll | [A] Attack (" << p.attack << ")" << std::endl; 
        std::cout << "> ";
        std::getline(std::cin, input);
        input_vec = tokenize(input);

        // Clean terminal
        //ClearTerminal();
        if (!input_vec.empty()) {
            // Exit 
            if (input_vec[0] == "exit") {
                return 0;
            }
            // Player's turn 
            if (this->turn == "player") {
                for (const auto& pl : players) {
                    pl->run_turn(input_vec);
                }
                checkStats(lvl.getEnemies());
            }
            // Enemy's turn
            if (this->turn == "enemy") {
                for (const auto& en : lvl.getEnemies()) {
                    en->run_turn(); 
                }
                checkStats(players);
            }
        }

        input_vec.clear(); // Clean up the token vector 
    }

    return 0;
}

Game::Game() {   
    this->seed = 42;
}

void Game::addMessage(const std::string& msg) {
    this->msgs.push_back(msg);
}

void Game::setTurn(const std::string& newTurn) {
    this->turn = newTurn;
    this->gen = std::mt19937(seed);
}

int Game::getSeed() {
    return this->seed; 
}

std::mt19937& Game::getGenerator() {
    return this->gen;
}

std::vector<Player*>& Game::getPlayers() {
    return players;
}

std::vector<Player*>& Game::getEnemies() {
    return currLvl->getEnemies();
}

Level* Game::getCurrLevel() {
    return currLvl;
}



// void Game::Update()
// {
//     UpdateGame();
// }

// void Game::Draw()
// {
//     DrawGame();
// }