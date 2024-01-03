from typing import Literal
from util import read_file_lines
from collections import defaultdict

def parse_input(mode: Literal["test", "input"]):
    input_lines = read_file_lines(f"day15/{mode}.txt")

    input_lines = input_lines[0].split(",")

    result = []

    for seq in input_lines:
        if "=" in seq:
            result.append(seq.split("="))
        elif "-" in seq:
            result.append([seq.split("-")[0]])

    return result

def hash(input_str: str) -> int:
    cur_val = 0
    for ch in input_str:
        cur_val += ord(ch)
        cur_val *= 17
        cur_val %= 256
    return cur_val

def solution():
    input_lines = parse_input("input")
    hashmap = defaultdict(list) 

    for entry in input_lines:
        box_label = hash(entry[0])

        label = entry[0]
        existing_indicies = [index for (index, item) in enumerate(hashmap[box_label]) if item[0] == label]
        if len(entry) == 1:
            if len(existing_indicies) != 0:
                del hashmap[box_label][existing_indicies[0]]
        elif len(entry) == 2:
            if len(existing_indicies) != 0:
                hashmap[box_label][existing_indicies[0]][1] = entry[1]
            else:
                hashmap[box_label].append([label, entry[1]])

    result = 0
    for key, value in hashmap.items():
        if len(value) == 0:
            continue
        for index, lens_entry in enumerate(value):
            result += (key + 1) * (index + 1) * int(lens_entry[1])
    return result

