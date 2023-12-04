#include "../src/aoc.hh"
#include <gtest/gtest.h>

TEST(Day3, Part1) {
    std::string input = "467..114..\n\
...*......\n\
..35..633.\n\
......#...\n\
617*......\n\
.....+.58.\n\
..592.....\n\
......755.\n\
...$.*....\n\
.664.598..";
    int res = day3p1(input);
    EXPECT_EQ(res, 4361);
}

TEST(Day3, Part2) {
    std::string input = "467..114..\n\
...*......\n\
..35..633.\n\
......#...\n\
617*......\n\
.....+.58.\n\
..592.....\n\
......755.\n\
...$.*....\n\
.664.598..";
    int res = day3p2(input);
    EXPECT_EQ(res, 467835);
}
