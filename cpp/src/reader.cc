#include <iostream>
#include <fstream>
#include <string>

std::string read_file(const char* path) {
    std::string res;
    std::ifstream file;
    char ch;
    if (path == NULL) {
        std::cin >> res;
    } else {
        file.open(path);
        while (file.is_open()) {
            while (file) {
                ch = file.get();
                res.push_back(ch);
            }
        }
    }
    return res;
}