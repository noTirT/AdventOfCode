from collections import defaultdict
from typing import Literal
from util import read_file_lines


def find_possible_lines(line: str):
    result = {}

    for left in range(len(line) - 1):
        inaccuracy = 0
        for offset in range(0, min(left, len(line) - left - 2) + 1):
            left_check, right_check = line[left - offset], line[left + offset + 1]
            if left_check != right_check:
                inaccuracy += 1
        if inaccuracy <= 1:
            result[(left, left + 1)] = inaccuracy
    return result


def merge_map_lists(possible_lines):
    temp = defaultdict(int)

    possible_keys = set(possible_lines[0].keys()).intersection(*[x.keys() for x in possible_lines[1:]])

    for possibilities in possible_lines:
        for key, value in possibilities.items():
            temp[key] += value

    result = []

    for key in possible_keys:
        if temp[key] == 1:
            result.append(key)
    print(result)
    return result


def test_vertical(pattern: str):
    possible_lines = []

    for line in pattern:
        possible_lines.append(find_possible_lines(line))

    possible_lines = merge_map_lists(possible_lines)

    return possible_lines


def test_horizontal(pattern):
    possible_lines = []

    for col in range(len(pattern[0])):
        possible_lines.append(
            find_possible_lines("".join([pattern[x][col] for x in range(len(pattern))]))
        )

    possible_lines = merge_map_lists(possible_lines)

    return possible_lines


def solve_pattern(pattern):
    hor_result = test_horizontal(pattern)
    vert_result = test_vertical(pattern)

    result = None
    print(hor_result, vert_result)
    if len(vert_result) == 1:
        vec = vert_result[0]
        result = vec[0] + 1
    elif len(hor_result) == 1:
        vec = hor_result[0]
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
        print(sum)
        print("\n".join(line))
    return sum
