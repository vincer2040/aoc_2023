package main

import (
	"aoc_2023/cmd/day1"
	"testing"
)

func TestDay1P1(t *testing.T) {
	input := `1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet`

	res := day1.Part1(input)

	exp := 142

	if res != exp {
		t.Fatalf("part1 expeced %d, got %d", exp, res)
	}

}

func TestDay1P2(t *testing.T) {
	input := `two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen`
	res := day1.Part2(input)
	exp := 281

	if res != exp {
		t.Fatalf("part2 expeced %d, got %d", exp, res)
	}
}
