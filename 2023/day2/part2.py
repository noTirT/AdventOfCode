from util import read_file_lines


file_path = "day2/input.txt"

input_lines = read_file_lines(file_path)


def sum_ids(input_lines):
    sum = 0
    for line in input_lines:
        game = read_game(line)
        sum += calculate_minimum_power(game)

    return sum


def calculate_minimum_power(game):
    power = 1

    for min_val in game["cubes"].values():
        power *= min_val

    return power


def read_game(line):
    cubes = {}
    first = line.split(": ")
    id = int(first[0].split(" ")[1])
    hands = first[1].split("; ")
    for hand in hands:
        cube_groups = hand.split(", ")
        for group in cube_groups:
            values = group.split(" ")
            cubes.setdefault(values[1], 0)
            cubes[values[1]] = max(cubes[values[1]], int(values[0]))
    return {"id": id, "cubes": cubes}


def solution():
    input_lines = read_file_lines("day2/input.txt")
    return sum_ids(input_lines)
