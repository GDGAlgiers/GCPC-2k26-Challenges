# Dungeon Escape — Editorial

## Tags
`BFS` `Grid` `State-Space Search` `Shortest Path`

## Problem Recap

You are given an $N \times M$ grid representing a dungeon. You start at `S` and must reach `E`. You can move up, down, left, or right one step at a time. Some cells are walls (`#`), some are locked doors (`K`) that can only be passed after picking up a key (`k`). There is at most one key. Find the minimum number of steps, or `-1` if impossible.

## Key Observation
> The presence of a single key means the entire state of the player is defined by **two pieces of information**: the current cell and whether the key has been collected. This leads to a state space of size $2 \times N \times M$, which is small enough to explore exhaustively with BFS.

## Approach

We use **Breadth‑First Search (BFS)** to explore all reachable states in order of increasing distance from the start.

### Step 1: Represent the State

Define a state as a tuple `(row, col, hasKey)` where `hasKey` is `0` (false) or `1` (true).

### Step 2: Initialise BFS

- Locate the starting cell `S` and set the initial state to `(start_r, start_c, 0)`.
- Create a 3D boolean array `visited[N][M][2]` to mark states already processed.
- Use a queue (FIFO) to hold states along with the current step count.

### Step 3: Process the Queue

While the queue is not empty:

1. Dequeue the front state `(r, c, hasKey, steps)`.
2. If the current cell is `E`, return `steps` as the answer.
3. For each of the four directions `(dr, dc)`:
   - Compute new coordinates `(nr, nc) = (r+dr, c+dc)`.
   - Check if `(nr, nc)` is within the grid bounds.
   - Let `cell = grid[nr][nc]`.
   - If `cell == '#'`, skip (wall).
   - If `cell == 'K'` and `hasKey == 0`, skip (locked door).
   - Determine the new key status: `newKey = hasKey or (cell == 'k')`.
   - If `visited[nr][nc][newKey]` is false, mark it true and enqueue `(nr, nc, newKey, steps + 1)`.

### Step 4: No Path Found

If the queue is exhausted without reaching `E`, output `-1`.

## Complexity
- **Time:** $O(N \cdot M)$ — each cell is visited at most twice (once with key, once without).
- **Space:** $O(N \cdot M)$ — for the visited array and the BFS queue.

Both are well within limits for $N, M \leq 500$.

## Implementation Notes
- In Python, use `collections.deque` for efficient $O(1)$ pops from the front.
- Ensure the visited array is large enough to index `hasKey` as 0 or 1.
- The grid is given as a list of strings; you can index them directly.

### Python Solution

```python
from collections import deque

def solve():
    import sys
    input = sys.stdin.read
    data = input().split()
    if not data:
        return
    N, M = int(data[0]), int(data[1])
    grid = data[2:]

    # Find start position
    sr = sc = None
    for i in range(N):
        for j in range(M):
            if grid[i][j] == 'S':
                sr, sc = i, j
                break
        if sr is not None:
            break

    visited = [[[False, False] for _ in range(M)] for _ in range(N)]
    q = deque()
    q.append((sr, sc, 0, 0))
    visited[sr][sc][0] = True

    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    while q:
        r, c, hasKey, steps = q.popleft()
        if grid[r][c] == 'E':
            print(steps)
            return
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < N and 0 <= nc < M:
                cell = grid[nr][nc]
                if cell == '#':
                    continue
                if cell == 'K' and not hasKey:
                    continue
                newKey = hasKey or (cell == 'k')
                if not visited[nr][nc][newKey]:
                    visited[nr][nc][newKey] = True
                    q.append((nr, nc, newKey, steps + 1))

    print(-1)

if __name__ == "__main__":
    solve()
```

## Example Walkthrough

### Sample Input

```
5 5
S...K
###.#
k...E
###.#
.....
```

- Start at `(0,0)` with no key.

- BFS expands rightwards: (0,1), (0,2), (0,3). From (0,3), right is `K` – blocked.

- Down from (0,3) to (1,3) is allowed; continue down to (2,3).

- From (2,3) move leftwards to reach the key at (2,0), acquiring the key.

- With the key, return to (0,3) and pass through `K` to the right side, then down to `E`.

- The BFS finds this path in 9 steps.

## Common Pitfalls
- Forgetting the `hasKey` dimension in `visited` – this will cause the algorithm to ignore paths that return to a cell with the key after visiting it earlier without the key.

- Allowing passage through `K` without checking `hasKey` – locked doors are impassable until the key is obtained.

- Using DFS instead of BFS – DFS does not guarantee the shortest path in an unweighted grid.

## Alternative Approaches
- **Dijkstra’s Algorithm**: Overkill because all moves cost 1; BFS is sufficient and simpler.

- **A Search**: Could be faster with a good heuristic (e.g., Manhattan distance), but BFS is already efficient enough.
