package main

import (
	"fmt"
	"strconv"

	"github.com/noTirT/AdventOfCode/2022/day1"
)

func GetProblemNumber() int8 {
	var problemNumber int8

	for {
		var input string

		fmt.Print("Enter the day number [0-25] you want to run: ")

		fmt.Scan(&input)

		inputInt, err := strconv.Atoi(input)
		if err != nil {
			fmt.Println("Invalid. Please enter a nummber in range from 1 through 25")
			continue
		}
		if 1 <= inputInt && inputInt <= 25 {
			problemNumber = int8(inputInt)
			break
		}
		fmt.Println("Invalid. Please enter a nummber in range from 1 through 25")
	}
	return problemNumber
}

func DisplayResults(part1 func() int, part2 func() int) {
	result1 := part1()
	result2 := part2()

	fmt.Printf("Result for part 1: %d\nResult for part 2: %d\n", result1, result2)
}

func main() {
	problemNumber := GetProblemNumber()

	functions := [][]func() int{
		{day1.Solution01, day1.Solution02},
	}

	currFunctions := functions[problemNumber-1]

	DisplayResults(currFunctions[0], currFunctions[1])
}
