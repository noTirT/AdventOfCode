from typing import Literal
from util import read_file_lines

mode: Literal["test", "input"] = "input"

file_lines = list(map(list, read_file_lines(f"day11/{mode}.txt")))

result = []

empty_row_indicies = [
    idx for idx, value in enumerate(file_lines) if all(el == "." for el in value)
]

empty_col_indicies = []

for col in range(len(file_lines[0])):
    curr_col = [file_lines[row][col] for row in range(len(file_lines))]

    if all(el == "." for el in curr_col):
        empty_col_indicies.append(col)

galaxy_locations = {}

galaxy_num = 0
for r_index, row in enumerate(file_lines):
    for c_index, col in enumerate(file_lines[r_index]):
        if col == "#":
            galaxy_num += 1
            galaxy_locations[galaxy_num] = (r_index, c_index)


def get_distance(g1: [int, int], g2: [int, int]):
    additional_x_distance = len(
        [x for x in empty_col_indicies if min(g1[1], g2[1]) < x < max(g1[1], g2[1])]
    )
    additional_y_distance = len(
        [x for x in empty_row_indicies if min(g1[0], g2[0]) < x < max(g1[0], g2[0])]
    )
    return (
        abs(g1[0] - g2[0])
        + abs(g1[1] - g2[1])
        + additional_x_distance
        + additional_y_distance
    )


distances = {}

for i in range(1, galaxy_num):
    for j in range(i + 1, galaxy_num + 1):
        distances[(i, j)] = get_distance(galaxy_locations[i], galaxy_locations[j])


def solution():
    return sum(distances.values())
