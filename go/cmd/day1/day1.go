package day1

import (
	"bufio"
	"strings"
)

func Part1(input string) int {
	scanner := bufio.NewScanner(strings.NewReader(input))
	res := 0
	for scanner.Scan() {
		line := scanner.Text()
		num1 := -1
		num2 := -1
		for _, ch := range line {
			if '0' <= ch && ch <= '9' {
				if num1 == -1 {
					num1 = int(ch - '0')
				}
				num2 = int(ch - '0')
			}
		}
		num := (num1 * 10) + num2
		res += num
	}
	return res
}

type LookupItem struct {
	str string
	num int
}

var lookupTable = []LookupItem{
	{"one", 1},
	{"two", 2},
	{"three", 3},
	{"four", 4},
	{"five", 5},
	{"six", 6},
	{"seven", 7},
	{"eight", 8},
	{"nine", 9},
}

func lookup(str string) int {
	for _, item := range lookupTable {
		if strings.HasPrefix(str, item.str) {
			return item.num
		}
	}
	return -1
}

func Part2(input string) int {
	scanner := bufio.NewScanner(strings.NewReader(input))
	res := 0
	for scanner.Scan() {
		line := scanner.Text()
		lineLen := len(line)
		num1 := -1
		num2 := -1
		for i, ch := range line {
			sub := line[i:lineLen]
			lookupInt := lookup(sub)
			if lookupInt != -1 {
				if num1 == -1 {
					num1 = lookupInt
				}
				num2 = lookupInt
			} else {
				if '0' <= ch && ch <= '9' {
					if num1 == -1 {
						num1 = int(ch - '0')
					}
					num2 = int(ch - '0')
				}
			}
		}
		num := (num1 * 10) + num2
		res += num
	}
	return res
}
