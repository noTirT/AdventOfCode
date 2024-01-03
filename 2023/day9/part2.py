from typing import List, Literal

from util import read_file_lines


def parse_input(mode: Literal["test", "input"]):
    input_lines = read_file_lines(f"day9/{mode}.txt")

    sequences = []
    for line in input_lines:
        sequences.append(list(map(lambda num: int(num), line.split(" "))))
    return sequences


def calculate_sequence(sequence: List[int]) -> List[int]:
    all_sequences = [sequence]

    while not all(x == 0 for x in all_sequences[-1]):
        all_sequences.append(get_next_sequence(all_sequences[-1]))

    all_sequences[-1].insert(0, 0)
    for curr_rank in range(len(all_sequences) - 2, -1, -1):
        to_append = all_sequences[curr_rank][0] - all_sequences[curr_rank + 1][0]
        all_sequences[curr_rank].insert(0, to_append)
    return all_sequences[0]


def get_next_sequence(sequence: List[int]) -> List[int]:
    return [sequence[i + 1] - sequence[i] for i in range(len(sequence) - 1)]


def solution():
    sequences = parse_input("input")

    result = 0
    for sequence in sequences:
        result += calculate_sequence(sequence)[0]
    return result
