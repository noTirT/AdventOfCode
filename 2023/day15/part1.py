from typing import Literal
from util import read_file_lines

def parse_input(mode: Literal["test", "input"]):
    input_lines = read_file_lines(f"day15/{mode}.txt")

    return input_lines[0].split(",")

def hash(input_str: str) -> int:
    cur_val = 0
    for ch in input_str:
        cur_val += ord(ch)
        cur_val *= 17
        cur_val %= 256
    return cur_val

def solution():
    input_lines = parse_input("input")

    hash_codes = map(lambda step: hash(step), input_lines)

    return sum(hash_codes)
