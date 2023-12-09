package day2

import (
	"github.com/noTirT/AdventOfCode/2022/util"
)

func Solution02() int {
	lines := util.GetFileLines("./day2/input.txt")

	totalScore := 0

	for _, line := range lines {
		switch line {
		case "A Y", "B X", "C Z":
			totalScore += 1
		case "A Z", "B Y", "C X":
			totalScore += 2
		case "A X", "B Z", "C Y":
			totalScore += 3
		}

		switch line[2:] {
		case "Y":
			totalScore += 3
		case "Z":
			totalScore += 6
		}
	}

	return totalScore
}
