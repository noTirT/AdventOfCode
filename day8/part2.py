from math import lcm
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


def n_steps(node, steps, routing):
    count = 0
    while node[0][2] != "Z":
        step = steps[count % len(steps)]
        curr_key = node[0]
        if step == "L":
            curr_key = routing[curr_key][0]
        if step == "R":
            curr_key = routing[curr_key][1]
        node = (curr_key, routing[curr_key])
        count += 1
    return count


def solution():
    instructions, routing = parse_input("input")

    curr_nodes = [n for n in list(routing.items()) if n[0][2] == "A"]

    lens = [n_steps(node, instructions, routing) for node in curr_nodes]

    return lcm(*lens)
