#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split_str(const std::string& str, char ch) {
    std::vector<std::string> res;
    std::istringstream iss(str);
    std::string sub;
    while (std::getline(iss, sub, ch)) {
        res.push_back(sub);
    }
    return res;
}

std::vector<std::string> split_on_string(const std::string& str, const std::string& delim) {
    std::vector<std::string> res;
    size_t pos = 0;
    size_t found;
    while ((found = str.find(delim, pos)) != std::string::npos) {
        res.push_back(str.substr(pos, found - pos));
        pos = found + delim.length();
    }
    res.push_back(str.substr(pos));
    return res;
}

std::string trim(const std::string& str) {
    auto start = str.begin();
    auto end = str.end();

    while (start != end && std::isspace(*start)) {
        ++start;
    }

    while (start != end && std::isspace(*(end - 1))) {
        --end;
    }

    return std::string(start, end);
}

size_t num_lines(const std::string& str) {
    size_t res = 0;
    for (auto c : str) {
        if (c == '\n') {
            res++;
        }
    }
    return res;
}
