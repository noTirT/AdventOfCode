package day1

import (
	"log"
	"strconv"

	"github.com/noTirT/AdventOfCode/2022/util"
)

func Solution01() int {
	lines := util.GetFileLines("./day1/input.txt")

	maxSum := 0
	currSum := 0

	for _, line := range lines {
		if line != "" {
			currVal, err := strconv.Atoi(line)
			if err != nil {
				log.Fatal(err)
			}
			currSum += currVal
		} else {
			if currSum > maxSum {
				maxSum = currSum
			}
			currSum = 0
		}
	}
	return maxSum
}
