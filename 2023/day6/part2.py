from typing import List
from util import read_file_lines


def parse_input(lines: List[str]) -> List[int]:
    time = "".join(lines[0].split(":")[1].split())

    distance = "".join(lines[1].split(":")[1].split())

    return int(time), int(distance)


def calculate_beating_distances(max_time: int, distance_to_beat: int) -> List[int]:
    count = 0
    for time_held in range(1, max_time):
        if time_held * (max_time - time_held) > distance_to_beat:
            count += 1
    return count


def solution():
    input_lines = read_file_lines("day6/input.txt")

    time, distance = parse_input(input_lines)

    return calculate_beating_distances(time, distance)
