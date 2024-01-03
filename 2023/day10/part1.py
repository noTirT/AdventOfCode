from collections import deque
from typing import Literal

from util import read_file_lines


def parse_input(mode: Literal["test", "input"]):
    return list(map(list, read_file_lines(f"day10/{mode}.txt")))


sketch = parse_input("input")
row_amount = len(sketch)
col_amount = len(sketch[0])


def find_start():
    for row in range(len(sketch)):
        for col in range(len(sketch[row])):
            if sketch[row][col] == "S":
                return [row, col]


def get_dir_neighbors(row, col):
    res = []
    if sketch[row][col] == "S":
        for drow, dcol in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            nrow, ncol = row + drow, col + dcol
            if not (0 <= nrow < row_amount and 0 <= ncol < col_amount):
                continue
            if (row, col) in list(get_neigbors(nrow, ncol)):
                res.append((drow, dcol))
        return res
    else:
        res = {
            "|": [(1, 0), (-1, 0)],
            "-": [(0, 1), (0, -1)],
            "L": [(-1, 0), (0, 1)],
            "J": [(-1, 0), (0, -1)],
            "7": [(1, 0), (0, -1)],
            "F": [(1, 0), (0, 1)],
            ".": [],
        }[sketch[row][col]]
        return res


def get_neigbors(row, col):
    res = []
    for dir_row, dir_col in list(get_dir_neighbors(row, col)):
        new_row, new_col = row + dir_row, col + dir_col
        if not (0 <= new_row < row_amount and 0 <= new_col < col_amount):
            continue
        res.append((new_row, new_col))
    return res


def solution():
    si, sj = find_start()

    visited = set()
    distances = {}
    q = deque([((si, sj), 0)])
    while len(q) > 0:
        top, dist = q.popleft()
        if top in visited:
            continue
        visited.add(top)
        distances[top] = dist

        for neighbor in list(get_neigbors(*top)):
            if neighbor in visited:
                continue
            q.append((neighbor, dist + 1))

    result = max(distances.values())
    return result
