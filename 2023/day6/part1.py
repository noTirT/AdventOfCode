from typing import List
from util import read_file_lines


def parse_input(lines: List[str]) -> List[List[int]]:
    result = []

    times = " ".join(lines[0].split(":")[1].split()).split(" ")

    distances = " ".join(lines[1].split(":")[1].split()).split(" ")

    for i in range(len(times)):
        result.append([int(times[i]), int(distances[i])])

    return result


def calculate_possible_distances(max_time: int) -> List[int]:
    possibilities = []
    for time_held in range(1, max_time):
        possibilities.append(time_held * (max_time - time_held))
    return possibilities


def solution():
    input_lines = read_file_lines("day6/input.txt")

    time_distance_list = parse_input(input_lines)

    result = 1

    for el in time_distance_list:
        time, record_distance = el
        possible_distances = calculate_possible_distances(time)
        result *= len(
            list(
                filter(lambda distance: distance > record_distance, possible_distances)
            )
        )

    return result
