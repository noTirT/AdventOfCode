from util import read_file_lines
from typing import List, Literal
from copy import deepcopy

def print_platform(platform: List[List[str]]):
    for row in platform:
        print("".join(row))
    print("\n")

def tilt_north(platform: List[List[str]]):
    curr_block = -1
    
    for col in range(len(platform[0])):
        for row in range(len(platform)):
            if platform[row][col] == "O":
                platform[row][col] = "."
                platform[curr_block + 1][col] = "O"
                curr_block = curr_block + 1
            elif platform[row][col] == "#":
                curr_block = row
        curr_block = -1
    return platform

def tilt_west(platform: List[List[str]]):
    curr_block = -1

    for row in range(len(platform)):
        for col in range(len(platform[0])):
            if platform[row][col] == "O":
                platform[row][col] = "."
                platform[row][curr_block + 1] = "O"
                curr_block += 1
            elif platform[row][col] == "#":
                curr_block = col 
        curr_block = -1
    return platform

def tilt_south(platform: List[List[str]]):
    curr_block = len(platform)

    for col in range(len(platform[0])):
        for row in range(len(platform)-1, -1, -1):
            if platform[row][col] == "O":
                platform[row][col] = "."
                platform[curr_block - 1][col] = "O"
                curr_block -= 1
            elif platform[row][col] == "#":
                curr_block = row
        curr_block = len(platform)
    return platform

def tilt_east(platform:List[List[str]]):
    curr_block = len(platform[0])

    for row in range(len(platform)-1, -1, -1):
        for col in range(len(platform[0])-1, -1, -1):
            if platform[row][col] == "O":
                platform[row][col] = "."
                platform[row][curr_block -1] = "O"
                curr_block -= 1
            elif platform[row][col] == "#":
                curr_block = col 
        curr_block = len(platform[0])
    return platform

def do_cycle(platform: List[List[str]]):
    return tilt_east(tilt_south(tilt_west(tilt_north(platform))))

def calc_total_load(platform: List[List[str]]):
    total = 0
    for row in range(len(platform)):
        for col in range(len(platform[0])):
            if platform[row][col] == "O":
                total += len(platform) - row
    return total

def platform_to_string(platform: List[List[str]]):
    result = ""
    for row in platform:
        result += "".join(row)
    return result

def parse_input(mode: Literal["test", "input"]):
    lines = read_file_lines(f"day14/{mode}.txt")

    return [list(line) for line in lines]

def solution():
    input_lines = parse_input("input")
    
    cycle2grid = {}
    seen = {}

    for cycle in range(10**9):
        input_lines = do_cycle(input_lines)

        h = platform_to_string(input_lines)

        if h in seen:
            period = cycle - seen[h]
            ans_grid = cycle2grid[(10**9 - 1 - seen[h]) % period + seen[h]]
            return calc_total_load(ans_grid)
        seen[platform_to_string(input_lines)] = cycle
        cycle2grid[cycle] = deepcopy(input_lines)
