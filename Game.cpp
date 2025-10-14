#include "Game.h"
//#include "raylib.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <random> // For random number generation
// #include <unordered_set>

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

std::mt19937 gen(42); // Seed

int rollDice() {
    std::uniform_int_distribution<> distrib(1, 6); // Uniform integer dist
    int random_number = distrib(gen);
    return random_number;
}

void printStats(Player p) {
    std::cout << "| == " << p.name << " Stats == | " << p.attack << std::endl;
    std::cout << "| Attack: " << p.attack << std::endl;
    std::cout << "| Defense: " << p.defense << std::endl;
    std::cout << "| Health: " << p.health << std::endl;
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

    
    Player p = Player( "Player" );      // Player  
    Player enemy = Player( "Monster" );  // Enemy 
    std::string turn = "player";

    while (true) {
        printStats(p); 
        std::cout << "Actions: " << std::endl;
        std::cout << "[R] Roll | [A] Attack (" << p.attack << ")" << std::endl; 
        std::cout << "> ";
        std::getline(std::cin, input);
        input_vec = tokenize(input);

        // Clean terminal
        ClearTerminal();
        if (!input_vec.empty()) {
            // Exit 
            if (input_vec[0] == "exit") {
                break;
            }
            // Roll 
            else if (input_vec[0] == "R") {
                p.roll = rollDice();
                // Lose turn 
                if (p.roll == 1 ){
                    p.attack = 0;
                    turn = "enemy"; // Player loses its turn 
                }
                // Double damage
                else if (p.roll == 6){
                    p.attack = p.attack * 2; 
                }
                // Normal roll
                else {
                    p.attack += p.roll; 
                }
            }
            // Attack
            else if (input_vec[0] == "A") {
                std::cout << "Attacked enemy: -" << p.attack << std::endl;
                p.attack = 0; 
                turn = "enemy"; // Finished turn 
            }
            else {
                std::cout << input_vec[0] << ": command not found" << std::endl;
            }

            // Enemy's turn
            if (turn != "player") {
                enemy.roll = rollDice();
                std::cout << "Enemy rolled: " << enemy.roll << std::endl;
                enemy.attack += enemy.roll;
                std::cout << "Enemy attacked " << enemy.attack << std::endl;
                p.health = p.health - std::abs( enemy.attack - p.defense );
                enemy.attack = 0;
                turn = "player"; // finish turn 
            }
        }

        input_vec.clear(); // Clean up the token vector 
    }

    return 0;
}

Game::Game() {   
    
}

// void Game::Update()
// {
//     UpdateGame();
// }

// void Game::Draw()
// {
//     DrawGame();
// }