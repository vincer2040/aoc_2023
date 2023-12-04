#include "aoc.hh"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

int day4p1(const std::string& input) {
    std::istringstream iss(input);
    std::string line;
    int res = 0;
    while (std::getline(iss, line, '\n')) {
        std::vector<std::string> split = split_str(line, ':');
        std::string game = split[1];
        std::vector<std::string> game_split = split_str(game, '|');
        std::vector<std::string> win_str_nums =
            split_str(trim(game_split[0]), ' ');
        std::vector<std::string> got_str_nums =
            split_str(trim(game_split[1]), ' ');
        std::vector<int> win_nums;
        std::vector<int> got_nums;
        for (auto& s : win_str_nums) {
            if (s != "") {
                win_nums.push_back(std::stoi(trim(s)));
            }
        }
        for (auto& s : got_str_nums) {
            if (s != "") {
                got_nums.push_back(std::stoi(trim(s)));
            }
        }

        int cur = 0;

        for (auto& n : win_nums) {
            auto it = std::find(got_nums.begin(), got_nums.end(), n);
            if (it != got_nums.end()) {
                cur++;
            }
        }
        if (cur != 0) {
            res += std::pow(2, (cur - 1));
        }
    }
    return res;
}

int day4p2(const std::string& input) {
    size_t nl = num_lines(input);
    std::istringstream iss(input);
    std::string line;
    int res = 0;
    std::vector<int> played;
    played.reserve(nl);
    size_t i, cur_line_num = 0;
    for (i = 0; i < nl; ++i) {
        played.push_back(0);
    }
    while (std::getline(iss, line, '\n')) {
        std::vector<std::string> split = split_str(line, ':');
        std::string game = split[1];
        std::vector<std::string> game_split = split_str(game, '|');
        std::vector<std::string> win_str_nums =
            split_str(trim(game_split[0]), ' ');
        std::vector<std::string> got_str_nums =
            split_str(trim(game_split[1]), ' ');
        std::vector<int> win_nums;
        std::vector<int> got_nums;
        played[cur_line_num] += 1;
        for (auto& s : win_str_nums) {
            if (s != "") {
                win_nums.push_back(std::stoi(trim(s)));
            }
        }
        for (auto& s : got_str_nums) {
            if (s != "") {
                got_nums.push_back(std::stoi(trim(s)));
            }
        }
        size_t w, cur = 0;

        for (auto& n : win_nums) {
            auto it = std::find(got_nums.begin(), got_nums.end(), n);
            if (it != got_nums.end()) {
                cur++;
            }
        }

        for (w = 0; w < cur; ++w) {
            played[w + cur_line_num + 1] += played[cur_line_num];
        }
        cur_line_num++;
    }

    for (auto n : played) {
        res += n;
    }
    return res;
}
