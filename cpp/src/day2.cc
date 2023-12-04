#include "aoc.hh"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int day2p1(const std::string& input) {
    std::istringstream iss(input);
    std::string line;
    int res = 0;

    while (std::getline(iss, line, '\n')) {
        std::vector<std::string> split = split_str(line, ':');
        std::string& game_id_str = split[0];
        std::string& game_str = split[1];
        std::string& id_str = game_id_str.replace(0, 5, "");
        int id = std::stoi(id_str);

        std::vector<std::string> pulls = split_str(game_str, ';');
        bool possible = true;
        for (auto& pull_str : pulls) {
            std::string pull = trim(pull_str);
            std::vector<std::string> cube_strs = split_str(pull, ',');
            for (auto& cube_str_ : cube_strs) {
                std::string cube_str = trim(cube_str_);
                std::vector<std::string> num_and_color =
                    split_str(cube_str, ' ');
                int number = std::stoi(num_and_color[0]);
                std::string& color = num_and_color[1];
                if (color == "green") {
                    if (number > 13) {
                        possible = false;
                    }
                } else if (color == "blue") {
                    if (number > 14) {
                        possible = false;
                    }
                } else if (color == "red") {
                    if (number > 12) {
                        possible = false;
                    }
                }
            }
        }
        if (possible) {
            res += id;
        }
    }
    return res;
}

int day2p2(const std::string& input) {
    std::istringstream iss(input);
    std::string line;
    int res = 0;

    while (std::getline(iss, line, '\n')) {
        std::vector<std::string> split = split_str(line, ':');
        std::string& game_str = split[1];

        std::vector<std::string> pulls = split_str(game_str, ';');
        int full;
        int green_amt = 0;
        int blue_amt = 0;
        int red_amt = 0;
        for (auto& pull_str : pulls) {
            std::string pull = trim(pull_str);
            std::vector<std::string> cube_strs = split_str(pull, ',');
            for (auto& cube_str_ : cube_strs) {
                std::string cube_str = trim(cube_str_);
                std::vector<std::string> num_and_color =
                    split_str(cube_str, ' ');
                int number = std::stoi(num_and_color[0]);
                std::string& color = num_and_color[1];
                if (color == "green") {
                    if (number > green_amt) {
                        green_amt = number;
                    }
                } else if (color == "blue") {
                    if (number > blue_amt) {
                        blue_amt = number;
                    }
                } else if (color == "red") {
                    if (number > red_amt) {
                        red_amt = number;
                    }
                }
            }
        }
        full = blue_amt * red_amt * green_amt;
        res += full;
    }
    return res;
}
