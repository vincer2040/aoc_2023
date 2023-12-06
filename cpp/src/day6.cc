#include "aoc.hh"
#include <cstdint>
#include <iostream>
#include <math.h>

static std::vector<uint64_t> parse_nums(const std::string& s);
static uint64_t get_possible_ways_to_win(uint64_t time, uint64_t dist);
static uint64_t parse_num(const std::string& s);

uint64_t day6p1(const std::string& input) {
    uint64_t res = 1;
    std::vector<std::string> split = split_str(input, '\n');
    std::string times_str = split[0].replace(0, 6, "");
    std::string distances_str = split[1].replace(0, 10, "");
    std::vector<uint64_t> times = parse_nums(times_str);
    std::vector<uint64_t> distances = parse_nums(distances_str);
    size_t i, len = times.size();
    for (i = 0; i < len; ++i) {
        uint64_t time = times[i];
        uint64_t dist = distances[i];
        res *= get_possible_ways_to_win(time, dist);
    }
    return res;
}

uint64_t day6p2(const std::string& input) {
    std::vector<std::string> split = split_str(input, '\n');
    std::string times_str = split[0].replace(0, 6, "");
    std::string distances_str = split[1].replace(0, 10, "");
    uint64_t time = parse_num(times_str);
    uint64_t dist = parse_num(distances_str);
    return get_possible_ways_to_win(time, dist);
}

static std::vector<uint64_t> parse_nums(const std::string& s) {
    std::vector<uint64_t> res;
    size_t pos = 0, len = s.length();
    while (pos < len) {
        char ch = s[pos];
        if (isdigit(ch)) {
            uint64_t cur = 0;
            while (pos < len && isdigit(s[pos])) {
                cur = (cur * 10) + (s[pos] - '0');
                pos++;
            }
            res.push_back(cur);
            continue;
        }
        pos++;
    }
    return res;
}

static uint64_t parse_num(const std::string& s) {
    uint64_t res = 0;
    size_t pos = 0, len = s.length();
    while (pos < len) {
        char ch = s[pos];
        if (isdigit(ch)) {
            while (pos < len && isdigit(s[pos])) {
                res = (res * 10) + (s[pos] - '0');
                pos++;
            }
            continue;
        }
        pos++;
    }
    return res;
}

static uint64_t get_possible_ways_to_win(uint64_t time, uint64_t dist) {
    uint64_t d = time * time - 4 * dist;
    uint64_t sqrt_d = sqrt(d);
    if (sqrt_d * sqrt_d == d) {
        return sqrt_d - 1;
    } else {
        return sqrt_d + 1 - ((time & 1) ^ (sqrt_d & 1));
    }
}
