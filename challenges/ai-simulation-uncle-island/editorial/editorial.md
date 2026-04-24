# AI Simulation on Uncle Island — Editorial

## Tags
`geometry` `BFS` `polygon fill` `combinatorics` `expected value` `modular inverse`

## Key Observation
> Let $d_1 \le d_2 \le \cdots \le d_k$ be the **sorted Manhattan distances** from every integer point inside (or on the boundary of) the polygon to the nearest edge point. The expected maximum distance over all $2^k - 1$ non-empty subsets is:
> $$E[\max] = \frac{\displaystyle\sum_{i=1}^{k} d_i \cdot 2^{i-1}}{2^k - 1} \pmod{998244353}$$

## Approach

### Step 1 — Fill the polygon (mark all integer points on/inside)

The polygon is an **orthogonal polygon** (all interior angles are 90° or 270°). Use a scanline sweep:

- For each edge, mark the boundary cells on the grid.
- Simultaneously, build a **vertical-edge parity array** `add[x][y]`: increment when a vertical edge starts at $(x, y)$, decrement when it ends.
- While sweeping column $x$ from $y=0$ upwards, maintain a running parity `window[y]`. A cell $(x, y)$ is **interior** if `window[y]` is odd.
- Collect all boundary + interior cells.

Since all coordinates are $\le 2000$, the grid is at most $2001 \times 2001$.

### Step 2 — BFS for Manhattan distances

Run a **multi-source BFS** starting from all boundary cells simultaneously. Because the moves are 4-directional with unit cost, BFS distance equals Manhattan distance to the nearest boundary cell.

For each cell in the polygon, record its BFS distance into a list `vals`.

### Step 3 — Expected maximum formula

Sort `vals`. There are $k = |\text{vals}|$ citizens. The number of non-empty subsets is $2^k - 1$.

For each sorted value $d_i$ (1-indexed), the number of non-empty subsets where the maximum equals $d_i$ is exactly $2^{i-1}$ (include it, include any of the $i-1$ smaller-or-equal elements, exclude all larger elements). Therefore:

$$\sum_{\text{non-empty } S} \max(S) = \sum_{i=1}^{k} d_i \cdot 2^{i-1}$$

Divide by $2^k - 1$ using a modular inverse: $\text{ans} = \left(\sum_{i=1}^{k} d_i \cdot 2^{i-1}\right) \cdot (2^k - 1)^{-1} \bmod 998244353$.

## Complexity
- **Time:** $O(C^2)$ for fill + BFS where $C = 2000$ (dominated by the $2001 \times 2001$ grid scan).
- **Space:** $O(C^2)$

The $N \le 2 \times 10^6$ polygon vertices are no bottleneck because coordinates fit in the $2000 \times 2000$ grid.

## Common Pitfalls
- **Polygon fill direction**: the scanline parity must track vertical edges carefully (mark `add[x][y]` at every $(x, y)$ along a vertical edge, not just endpoints).
- **BFS only over valid cells**: `valid(nx, ny)` must check both bounds and `in[nx][ny]`.
- **Expected value denominator**: use Fermat's little theorem — $(2^k - 1)^{-1} \equiv (2^k - 1)^{p-2} \pmod{p}$ where $p = 998244353$.
- **Large $N$**: the loop over polygon edges runs in $O(N)$, not $O(C^2)$, because you step along each edge incrementally.

## Example Walkthrough

For the $2 \times 2$ square with vertices $(0,0),(2,0),(2,2),(0,2)$:

- Boundary cells (distance 0): $(0,0),(1,0),(2,0),(0,1),(2,1),(0,2),(1,2),(2,2)$ — 8 points.
- Interior cell (distance 1): $(1,1)$ — 1 point.
- `vals` (sorted) = $[0,0,0,0,0,0,0,0,1]$, $k = 9$.

$$\text{numerator} = 0 \cdot 1 + 0 \cdot 2 + \cdots + 0 \cdot 128 + 1 \cdot 256 = 256$$
$$\text{denominator} = 2^9 - 1 = 511$$
$$\text{ans} = 256 \cdot 511^{-1} \bmod 998244353 = 169955497$$

## Alternative Approaches
- **Precomputed distance transform**: for grids up to $2000\times2000$, a full BFS is efficient. No smarter data structure needed.
- If the polygon could have holes, BFS through valid cells would still be correct (shortest path ≤ Manhattan distance, but since it is a simple polygon, they are equal).
