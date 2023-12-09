package day2

import (
	"github.com/noTirT/AdventOfCode/2022/util"
)

func Solution01() int {
	lines := util.GetFileLines("./day2/input.txt")

	totalScore := 0

	for _, line := range lines {
		switch line {
		case "A Y", "B Z", "C X":
			totalScore += 6
		case "A X", "B Y", "C Z":
			totalScore += 3
		}

		switch line[2:] {
		case "X":
			totalScore += 1
		case "Y":
			totalScore += 2
		case "Z":
			totalScore += 3
		}
	}

	return totalScore
}
