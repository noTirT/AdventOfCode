from typing import List
import math

from util import read_file_lines


def parse_input(lines: List[str]) -> List[int]:
    time = "".join(lines[0].split(":")[1].split())

    distance = "".join(lines[1].split(":")[1].split())

    return [int(time), int(distance)]


def solution():
    input_lines = read_file_lines("day6/input.txt")
    time, distance = parse_input(input_lines)

    # f(x) = -(pressTime**2) + (time * pressTime) - distance
    delta = time**2 - (4 * distance)
    first_win_input = math.ceil(((-time) + math.sqrt(delta)) / 2 * (-1))
    second_win_input = math.floor(((-time) - math.sqrt(delta)) / 2 * (-1))

    secondTaskResult = second_win_input - first_win_input + 1
    return secondTaskResult
