#include "Game.h"
//#include "raylib.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <random>

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
    
    Player p     = Player( "Player", this);      // Player  
    Player enemy = Player( "Monster", this );  // Enemy 

    this->addMessage("Welcome!");

    while (true) {
        // Print a msg (if it exists)
        if (!msgs.empty()) {
            printMessage(msgs); 
        }
        p.printStats(); 
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
                break;
            }
            // Player's turn 
            if (this->turn == "player") {
                p.run_turn(input_vec); 
            }
            // Enemy's turn
            if (this->turn == "enemy") {
                enemy.run_turn();
                // enemy.roll = rollDice(1, 6);
                // std::cout << "Enemy rolled: " << enemy.roll << std::endl;
                // enemy.attack += enemy.roll;
                // std::cout << "Enemy attacked " << enemy.attack << std::endl;
                // p.health = p.health - std::abs( enemy.attack - p.defense );
                // enemy.attack = 0;
                // turn = "player"; // finish turn 
            }
            else {
                std::cerr << "Turn unidentified" << std::endl;
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

// void Game::Update()
// {
//     UpdateGame();
// }

// void Game::Draw()
// {
//     DrawGame();
// }