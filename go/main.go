package main

import (
	"aoc_2023/cmd/day1"
	"aoc_2023/internal/reader"
	"fmt"
)

func main() {
	input, err := reader.ReadFile(nil)
	if err != nil {
		fmt.Println(err)
		return
	}
	res := day1.Part2(input)
	fmt.Println(res)
}
