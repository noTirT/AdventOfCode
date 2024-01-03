from typing import Literal
from util import read_file_lines
from collections import deque

def parse_input(mode: Literal["test", "input"]):
    lines = read_file_lines(f"day16/{mode}.txt")

    return lines

def solution():
    lines = parse_input("input")

    # r, c, dr, dc
    a = [(0,-1,0,1)]
    seen = set()
    q = deque(a)

    while q:
        r,c,dr,dc = q.popleft()

        r += dr
        c += dc

        if r < 0 or r >= len(lines) or c < 0 or c >= len(lines[0]):
            continue

        ch = lines[r][c]

        if ch == "." or (ch == "-" and dc != 0) or (ch == "|" and dr != 0):
            if (r, c, dr, dc) not in seen:
                seen.add((r,c,dr,dc))
                q.append((r,c,dr,dc))
        elif ch == "/":
            dr, dc = -dc, -dr
            
            if (r, c, dr, dc) not in seen:
                seen.add((r,c,dr,dc))
                q.append((r,c,dr,dc))
        elif ch == "\\":
            dr, dc = dc, dr

            if (r, c, dr, dc) not in seen:
                seen.add((r,c,dr,dc))
                q.append((r,c,dr,dc))
        else:
            for dr, dc in [(1,0),(-1,0)] if ch == "|" else [(0,1), (0,-1)]:
                
                if (r, c, dr, dc) not in seen:
                    seen.add((r,c,dr,dc))
                    q.append((r,c,dr,dc))
    coord = {(r,c) for (r,c,_,_) in seen}
    return len(coord)
