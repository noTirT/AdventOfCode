from util import read_file_lines
from typing import List, Literal

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

def calc_total_load(platform: List[List[str]]):
    total = 0
    for row in range(len(platform)):
        for col in range(len(platform[0])):
            if platform[row][col] == "O":
                total += len(platform) - row
    return total

def parse_input(mode: Literal["test", "input"]):
    lines = read_file_lines(f"day14/{mode}.txt")

    return [list(line) for line in lines]

def solution():
    input_lines = parse_input("input")
    tilted_platform = tilt_north(input_lines)
    return calc_total_load(tilted_platform)
