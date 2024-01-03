from typing import Literal
from util import read_file_lines


def find_possible_lines(line: str):
    result = []

    for left in range(len(line)):
        add = True
        for offset in range(0, min(left, len(line) - left - 2) + 1):
            left_check, right_check = line[left - offset], line[left + offset + 1]
            if left_check != right_check:
                add = False
                break
        if add:
            result.append((left, left + 1))
    return result[:-1]


def test_vertical(pattern: str):
    possible_lines = []

    for line in pattern:
        possible_lines.append(find_possible_lines(line))

    return set(possible_lines[0]).intersection(*possible_lines[1:])


def test_horizontal(pattern):
    possible_lines = []

    for col in range(len(pattern[0])):
        possible_lines.append(
            find_possible_lines("".join([pattern[x][col] for x in range(len(pattern))]))
        )
    return set(possible_lines[0]).intersection(*possible_lines[1:])


def solve_pattern(pattern):
    vert_result = test_vertical(pattern)
    hor_result = test_horizontal(pattern)

    result = None
    if len(vert_result) == 1:
        vec = vert_result.pop()
        result = vec[0] + 1
    elif len(hor_result) == 1:
        vec = hor_result.pop()
        result = 100 * (vec[0] + 1)

    return result


def parse_input(mode: Literal["test", "input"]):
    patterns = []
    lines = read_file_lines(f"day13/{mode}.txt")
    temp_patterns = []
    for line in lines:
        if line != "":
            temp_patterns.append(line)
        else:
            patterns.append(temp_patterns)
            temp_patterns = []
    patterns.append(temp_patterns)

    return patterns


def solution():
    lines = parse_input("input")

    sum = 0
    for line in lines:
        sum += solve_pattern(line)
    return sum
