#pragma once

#include <cstdint>
#include <string>
#include <vector>

std::string read_file(const char* path);
std::vector<std::string> split_str(const std::string& str, char ch);
std::string trim(const std::string& str);
size_t num_lines(const std::string& str);

int day1p1(const std::string& input);
int day1p2(const std::string& input);

int day2p1(const std::string& input);
int day2p2(const std::string& input);

int day3p1(const std::string& input);
int day3p2(const std::string& input);

int day4p1(const std::string& input);
int day4p2(const std::string& input);

uint64_t day6p1(const std::string& input);
uint64_t day6p2(const std::string& input);

int day7p1(const std::string& input);
int day7p2(const std::string& input);
