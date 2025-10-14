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

int rollDice() {
    std::mt19937 gen(42); // Seed
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

    while (true) {
        std::cout << "Attack: " << cur_atk << std::endl;
        std::cout << "Actions: " << std::endl;
        std::cout << "[R] Roll" << std::endl; 
        std::cout << "> ";
        std::getline(std::cin, input);
        input_vec = tokenize(input);

        if (!input_vec.empty()) {
            // Exit 
            if (input_vec[0] == "exit") {
                break;
            }
            else if (input_vec[0] == "roll") {
                std::cout << "Rolled: " << std::endl;
                int cur_roll = rollDice();
                cur_atk = (cur_roll == 1) ? 0 : cur_atk += cur_roll;
            }
            else {
                std::cout << input_vec[0] << ": command not found" << std::endl;
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