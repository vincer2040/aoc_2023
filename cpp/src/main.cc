#include "aoc.hh"
#include <iostream>

int main(void) {
    std::string input = read_file(NULL);
    uint64_t res = day7p2(input);
    std::cout << res << '\n';
    return 0;
}
