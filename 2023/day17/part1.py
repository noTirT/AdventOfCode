from typing import Literal
from heapq import heappop, heappush
from util import read_file_lines

def parse_input(mode: Literal["test", "input"]):
    lines = read_file_lines(f"day17/{mode}.txt")

    result = []
    for row in range(len(lines)):
        temp = []
        for col in range(len(lines[row])):
            temp.append(int(lines[row][col]))
        result.append(temp)

    return result


def solution():
    grid = parse_input("input")

    seen = set()
    pq = [(0, 0, 0, 0, 0, 0)]

    while pq:
        hl, r, c, dr, dc, n = heappop(pq)

        if r == len(grid)-1 and c == len(grid[0])-1:
            return hl

        if r < 0 or r >= len(grid) or c < 0 or c >= len(grid[0]):
            continue

        if (r,c,dr,dc,n) in seen:
            continue

        seen.add((r,c,dr,dc,n))

        if n < 3 and (dr,dc) != (0,0):
            nr = r + dr
            nc = c + dc
            if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]):
                heappush(pq, (hl + grid[nr][nc], nr, nc, dr, dc, n+1))

        for ndr, ndc in [(1,0), (-1,0), (0,1), (0,-1)]:
            if (ndr, ndc) != (dr, dc) and (ndr, ndc) != (-dr, -dc):
                nr = r + ndr
                nc = c + ndc
                if 0 <= nr < len(grid) and 0 <= nc < len(grid[0]):
                    heappush(pq, (hl + grid[nr][nc], nr, nc, ndr, ndc, 1))
