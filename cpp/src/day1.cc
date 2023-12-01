#include "aoc.hh"
#include <cctype>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

int day1p1(const std::string& input) {
    std::istringstream iss(input);
    std::string line;
    int res = 0;
    while (std::getline(iss, line, '\n')) {
        int num1 = -1;
        int num2 = -1;
        for (auto& ch : line) {
            if (isdigit(ch)) {
                if (num1 == -1) {
                    num1 = ch - 48;
                }
                num2 = ch - 48;
            }
        }
        int num = (num1 * 10) + num2;
        res += num;
    }
    return res;
}

struct lookup {
    const char* str;
    size_t str_len;
    int num;
};

lookup lookups[] = {
    {"one", 3, 1},   {"two", 3, 2},   {"three", 5, 3},
    {"four", 4, 4},  {"five", 4, 5},  {"six", 3, 6},
    {"seven", 5, 7}, {"eight", 5, 8}, {"nine", 4, 9},
};

size_t lookups_len = sizeof lookups / sizeof lookups[0];

int lookup_str(const char* str) {
    size_t i;
    for (i = 0; i < lookups_len; ++i) {
        if (std::strncmp(lookups[i].str, str, lookups[i].str_len) == 0) {
            return lookups[i].num;
        }
    }
    return -1;
}

int day1p2(const std::string& input) {
    std::istringstream iss(input);
    std::string line;
    int res = 0;
    while (std::getline(iss, line, '\n')) {
        int num1 = -1;
        int num2 = -1;
        size_t i, len = line.length();
        for (i = 0; i < len; ++i) {
            std::string slice = line.substr(i, len - i);
            int lookup = lookup_str(slice.c_str());
            if (lookup == -1) {
                char ch = line[i];
                if (isdigit(ch)) {
                    if (num1 == -1) {
                        num1 = ch - 48;
                    }
                    num2 = ch - 48;
                }
            } else {
                if (num1 == -1) {
                    num1 = lookup;
                }
                num2 = lookup;
            }
        }
        int num = (num1 * 10) + num2;
        res += num;
    }
    return res;
}
