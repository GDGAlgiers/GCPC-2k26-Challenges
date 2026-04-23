import sys
from collections import deque
import numpy as np

def solve():
    def get_input():
        for line in sys.stdin:
            for word in line.split():
                yield word

    tokens = get_input()

    try:
        line1 = next(tokens)
    except StopIteration:
        return

    n = int(line1)
    p = []
    for _ in range(n):
        x = int(next(tokens))
        y = int(next(tokens))
        p.append((x, y))
    p.append(p[0])

    N = 2005
    mod = 998244353
    oo = 2 * 10**18

    # Use NumPy arrays for fast grid ops
    in_grid = np.zeros((N, N), dtype=np.int8)
    add_grid = np.zeros((N, N), dtype=np.int32)

    for i in range(1, n + 1):
        x,  y  = p[i]
        px, py = p[i - 1]

        min_y, max_y = min(py, y), max(py, y)
        min_x, max_x = min(px, x), max(px, x)

        in_grid[x, min_y:max_y + 1] = 1
        in_grid[min_x:max_x + 1, y] = 1
        add_grid[x, min_y:max_y] += 1


    window = np.zeros(N, dtype=np.int32)
    sources = []

    for x in range(N):
        col_in  = in_grid[x]           # shape (N,)
        col_add = add_grid[x]          # shape (N,)

        boundary_ys = np.where(col_in)[0]
        for y in boundary_ys:
            sources.append((x, y))

        interior = (window & 1).astype(np.int8)
        in_grid[x] |= interior

        window += col_add

    dist = np.full((N, N), oo, dtype=np.int64)

    q = deque()
    for x, y in sources:
        if dist[x][y] == oo:
            dist[x][y] = 0
            q.append((x, y))

    dx = (1, -1, 0, 0)
    dy = (0, 0, 1, -1)

    while q:
        x, y = q.popleft()
        d = dist[x][y]
        nd = d + 1
        for k in range(4):
            nx, ny = x + dx[k], y + dy[k]
            if 0 <= nx < N and 0 <= ny < N and dist[nx][ny] == oo and in_grid[nx][ny]:
                dist[nx][ny] = nd
                q.append((nx, ny))

    mask = in_grid.astype(bool)
    vals = dist[mask]
    vals_sorted = np.sort(vals)

    ans = 0
    pw = 1
    for v in vals_sorted:
        ans = (ans + int(v) * pw) % mod
        pw = pw * 2 % mod

    inv = pow((pw - 1) % mod, mod - 2, mod)
    print((ans * inv) % mod)

if __name__ == '__main__':
    solve()