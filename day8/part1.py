from typing import Literal
from util import read_file_lines


def parse_input(type: Literal["test", "input"]) -> str:
    input_lines = read_file_lines(f"day8/{type}.txt")

    instructions = input_lines[0]

    routing = {}

    for line_index in range(2, len(input_lines)):
        line = input_lines[line_index]

        val, routes = line.split(" = ")
        left, right = routes.replace("(", "").replace(")", "").split(", ")

        routing[val] = [left, right]

    return instructions, routing


def solution():
    instructions, routing = parse_input("input")

    curr_val = "AAA"
    curr_item = routing[curr_val]

    steps = 0

    instruction_step = 0

    while curr_val != "ZZZ":
        direction = instructions[instruction_step % len(instructions)]
        if direction == "R":
            curr_val = curr_item[1]
            curr_item = routing[curr_val]
        elif direction == "L":
            curr_val = curr_item[0]
            curr_item = routing[curr_val]
        steps += 1
        instruction_step += 1
    return steps
