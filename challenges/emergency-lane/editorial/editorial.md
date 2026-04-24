# Emergency Lane — Editorial

## Tags
`graph theory` `shortest paths` `dijkstra`

## Key Observation
> If an optimal route uses the priority pass on a road `(u, v)`, then the total
> cost becomes:
> shortest path from `1` to one endpoint + `0` for that road + shortest path
> from the other endpoint to `n`.

## Approach

### 1. Shortest distances from both ends

Run Dijkstra from city `1`:

- `dist_start[x]` = shortest distance from city `1` to city `x`

Run Dijkstra from city `n`:

- `dist_end[x]` = shortest distance from city `x` to city `n`

Both runs are on the original graph.

### 2. What happens if we use the pass on one road?

Suppose the free road is `(u, v)`.

Then one possible route is:

- shortest path from `1` to `u`
- traverse road `(u, v)` for free
- shortest path from `v` to `n`

Its cost is:

`dist_start[u] + dist_end[v]`

Because roads are bidirectional, we must also consider the other direction:

`dist_start[v] + dist_end[u]`

So the best route that uses the pass on road `(u, v)` is:

`min(dist_start[u] + dist_end[v], dist_start[v] + dist_end[u])`

### 3. Final answer

Initialize the answer as:

- `dist_start[n]`, meaning we do not use the pass at all

Then scan every road once and update the answer with the formula above.

If the answer stays infinite, print `-1`.

## Why This Works

Any optimal route that uses the pass has exactly one special road where the
discount is applied.

Everything before that road is just a normal shortest-path segment from city
`1` to one endpoint, and everything after that road is a normal shortest-path
segment from the other endpoint to city `n`.

So once the two distance arrays are known, every candidate discounted route is
fully determined by choosing the road that receives the pass.

## Complexity

- Two Dijkstra runs: **O(m log n)**
- Scan all roads once: **O(m)**
- Total: **O(m log n)**
- Space: **O(n + m)**

## Common Pitfalls

- Using 32-bit integers. Distances can exceed `2^31 - 1`.
- Forgetting to consider both directions of the discounted road.
- Assuming the pass must be used. The best answer may be the normal shortest
  path.
- Not handling disconnected graphs correctly.

## Example Walkthrough

For Sample 1:

- `dist_start[1] = 0`
- `dist_start[3] = 2`
- `dist_start[4] = 4`
- `dist_start[5] = 6`

Also, from city `5`:

- `dist_end[5] = 0`
- `dist_end[4] = 2`
- `dist_end[3] = 4`
- `dist_end[1] = 6`

Start with `answer = dist_start[5] = 6`.

Now check road `(4, 5)`:

- `dist_start[4] + dist_end[5] = 4 + 0 = 4`
- `dist_start[5] + dist_end[4] = 6 + 2 = 8`

Best with this road discounted = `4`, so the answer becomes `4`.

No other road gives a smaller value.

## Alternative Approaches

- A layered-graph Dijkstra on states `(city, used_pass)` also works.
- The two-Dijkstra solution is simpler and more direct for this exact problem.
