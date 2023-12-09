package day1

import (
	"log"
	"sort"
	"strconv"

	"github.com/noTirT/AdventOfCode/2022/util"
)

func Solution02() int {
	lines := util.GetFileLines("./day1/input.txt")

	sums := []int{0}
	for _, line := range lines {
		if line != "" {
			currVal, err := strconv.Atoi(line)
			if err != nil {
				log.Fatal(err)
			}
			sums[len(sums)-1] += currVal
		} else {
			sums = append(sums, 0)
		}
	}
	sort.Sort(sort.Reverse(sort.IntSlice(sums)))

	return sums[0] + sums[1] + sums[2]
}
