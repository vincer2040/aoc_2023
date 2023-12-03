package day2

import (
	"bufio"
	"strconv"
	"strings"
)

func Part1(input string) int {
	res := 0
	scanner := bufio.NewScanner(strings.NewReader(input))
	for scanner.Scan() {
		possible := true
		line := scanner.Text()
		split := strings.Split(line, ": ")
		id, _ := strconv.Atoi(strings.Split(split[0], " ")[1])
		gameStr := split[1]
		pulls := strings.Split(gameStr, "; ")
		for _, pull := range pulls {
			cubes := strings.Split(pull, ", ")
			for _, cube := range cubes {
				numColor := strings.Split(cube, " ")
				num, _ := strconv.Atoi(numColor[0])
				color := numColor[1]
				if color == "green" {
					if num > 13 {
						possible = false
					}
				} else if color == "blue" {
					if num > 14 {
						possible = false
					}
				} else if color == "red" {
					if num > 12 {
						possible = false
					}
				}
			}
		}
		if possible {
			res += id
		}
	}
	return res
}

func Part2(input string) int {
	res := 0
	scanner := bufio.NewScanner(strings.NewReader(input))
	for scanner.Scan() {
		line := scanner.Text()
		split := strings.Split(line, ": ")
		gameStr := split[1]
		pulls := strings.Split(gameStr, "; ")
		green_amt := 0
		blue_amt := 0
		red_amt := 0
		for _, pull := range pulls {
			cubes := strings.Split(pull, ", ")
			for _, cube := range cubes {
				numColor := strings.Split(cube, " ")
				num, _ := strconv.Atoi(numColor[0])
				color := numColor[1]
				if color == "green" {
					if num > green_amt {
						green_amt = num
					}
				} else if color == "blue" {
					if num > blue_amt {
						blue_amt = num
					}
				} else if color == "red" {
					if num > red_amt {
						red_amt = num
					}
				}
			}
		}
		full := green_amt * blue_amt * red_amt
		res += full
	}
	return res

}
