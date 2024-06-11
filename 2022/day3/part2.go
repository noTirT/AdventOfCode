package day3

import (
	"strings"

	"github.com/noTirT/AdventOfCode/2022/util"
)

func Solution02() int {
    lines := util.GetFileLines("./day3/test.txt")

    result := 0

    for i := 0; i<len(lines); i+=3{
        group := lines[i:i+3]

        chars1 := strings.Split(group[0], "")
        chars2 := strings.Split(group[1], "")
        chars3 := strings.Split(group[2], "")

        hash := make(map[string]struct{})
        for j := 0; j < len(chars1); j++{
            hash[chars1[j]] = struct{}{}
        }

        for j := 0; j<len(chars2); j++{
            hash[chars2[j]] = struct{}{}
        }

        var common string
        for j := 0; j<len(chars3); j++{
            if _,ok := hash[chars3[j]]; ok{
                common = chars3[j] 
            }
        }

        println(common)

    }

    return result 

}
