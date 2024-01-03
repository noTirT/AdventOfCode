from util import read_file_lines
from collections import deque

def solution():
    mode = "input"
    lines = read_file_lines(f"day21/{mode}.txt")

    sr, sc = [(r,c) for r, row in enumerate(lines) for c, ch in enumerate(row) if ch == "S"][0]

    ans = set()
    seen = {(sr, sc)}
    q = deque([(sr, sc, 64)])

    while q:
        r,c,s = q.popleft()

        if s % 2 == 0:
            ans.add((r,c))

        if s == 0:
            continue

        for nr, nc in [(r + 1, c), (r -1, c), (r, c + 1), (r, c - 1)]:
            if nr < 0 or nr >= len(lines) or nc < 0 or nc >= len(lines[0]) or lines[nr][nc] == "#" or (nr, nc) in seen:
                continue

            seen.add((nr, nc))
            q.append((nr, nc, s - 1))

    return len(ans)
