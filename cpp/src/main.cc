#include "aoc.hh"
#include <iostream>

int main(void) {
    std::string input = read_file(NULL);
    int res = day9p2(input);
    std::cout << res << '\n';
    return 0;
}
