#include "../src/aoc.hh"
#include <gtest/gtest.h>

TEST(Day1, Part1) {
    std::string input = "\
1abc2\n\
pqr3stu8vwx\n\
a1b2c3d4e5f\n\
treb7uchet";
    int res = day1p1(input);
    EXPECT_EQ(res, 142);
}

TEST(Day1, Part2) {
    std::string input = "\
two1nine\n\
eightwothree\n\
abcone2threexyz\n\
xtwone3four\n\
4nineeightseven2\n\
zoneight234\n\
7pqrstsixteen";
    int res = day1p2(input);
    EXPECT_EQ(res, 281);
}
