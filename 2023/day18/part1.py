from typing import Literal
from util import read_file_lines

dirs = {"U": (-1,0), "D": (1,0), "L": (0,-1), "R": (0,1)}

def parse_input(mode: Literal["test", "input"]):
    lines = read_file_lines(f"day18/{mode}.txt")

    points = [(0,0)]
    b = 0 
    for line in lines:
        d,n,_ = line.split()
        dr, dc = dirs[d]
        n = int(n)
        b += n
        r, c = points[-1]
        points.append((r + dr * n, c + dc * n))
    return b, points

def solution():
    b, points = parse_input("input")

    A = abs(sum(points[i][0] * (points[i-1][1] - points[(i+1) % len(points)][1]) for i in range(len(points)))) // 2

    i = A - b // 2 + 1

    return i + b
