package day3

import (
	"strings"

	"github.com/noTirT/AdventOfCode/2022/util"
)

func Solution01() int {
    lines := util.GetFileLines("./day3/input.txt")

    result := 0
    for _, line := range lines{
        chars := strings.Split(line, "")
        first_half := chars[0:len(chars) / 2]
        second_half := chars[len(chars)/2:]

        hash := make(map[string]struct{})

        var common string
        for i:= 0; i<len(first_half); i++ {
            hash[first_half[i]] = struct{}{}
        }

        for i:= 0; i<len(second_half); i++ {
            if _, ok := hash[second_half[i]]; ok{
                common = second_half[i]
            }
        }

        item := []byte(common)[0]
        if 'a' <= item && item <='z' {
            result += int(item - 'a' + 1)
        }else if 'A' <= item && item <= 'Z' {
            result += int(item - 'A' + 27)
        }
    }

    return result 

}
