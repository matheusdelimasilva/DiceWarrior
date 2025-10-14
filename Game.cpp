#include "Game.h"
#include "raylib.h"
// #include <cstdlib>
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
    std::cout << "Rolled: " << random_number << "." << std::endl;
    return random_number;
}

int Game::run() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf; // Flush after every std::cout / std:cerr
    std::string input;         // string containing user input 
    std::vector<std::string> input_vec; // Input break into tokens

    // Player stuff 
    int cur_roll = 1;
    int cur_atk = 0;

    // Enemy stuff
    int enemy_roll = 1;
    int enemy_atk = 0;

    // Current turn
    std::string turn = "player";

    while (true) {
        std::cout << "Attack: " << cur_atk << std::endl;
        std::cout << "Actions: " << std::endl;
        std::cout << "[R] Roll | [A] Attack (" << cur_atk << ")" << std::endl; 
        std::cout << "> ";
        std::getline(std::cin, input);
        input_vec = tokenize(input);

        if (!input_vec.empty()) {
            // Exit 
            if (input_vec[0] == "exit") {
                break;
            }
            else if (input_vec[0] == "R") {
                std::cout << "Rolled: " << std::endl;
                cur_roll = rollDice();
                if (cur_roll == 1 ){
                    cur_atk = 0;
                    turn = "player";
                }
                else {
                    cur_atk += cur_roll; 
                    turn = "enemy";
                }
            }
            else if (input_vec[0] == "A") {
                std::cout << "Attacked enemy: -" << cur_atk << std::endl;
                cur_atk = 0; 
            }
            else {
                std::cout << input_vec[0] << ": command not found" << std::endl;
            }

            // Monster's turn
            if (turn != "player") {
                enemy_roll = rollDice();
                enemy_atk += enemy_roll;
                std::cout << "Monster rolled: " << enemy_roll << std::endl;
                std::cout << "Monster attacked " << enemy_atk << std::endl;
                enemy_atk = 0;
                turn = "player";
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