# Midnight Relay Tour — Editorial

## Tags
`graph theory` `shortest paths` `bitmask dp` `held-karp` `dijkstra`

## Key Observation
> Once we know the shortest travel time between every important city
> (start, each relay city, and finish), the original graph can be compressed
> into a much smaller complete graph on only those cities.

## Approach
Let the important cities be:

- city `1` (start)
- the `k` damaged relay cities
- city `n` (finish)

There are at most `k + 2 <= 17` important cities, which is small.

### 1. Metric closure of the important cities

Run Dijkstra once from each important city on the original graph.

This gives us the shortest distance between every pair of important cities.
Call this matrix `dist_imp`.

This reduction is valid because any route can be split into segments between
important cities, and replacing each segment by the shortest path between its
endpoints never makes the route worse.

So after this step, the large graph has effectively been reduced to a weighted
complete graph on at most `17` nodes.

### 2. Bitmask DP over relay cities

Index the relay cities from `0` to `k - 1`.

Define:

`dp[mask][i]` = minimum cost to start at city `1`, visit exactly the relays in
`mask`, and finish at relay `i`.

Initialization:

- `dp[1 << i][i] = dist_imp[start][relay_i]`

Transition:

- from `dp[mask][i]`, try visiting any unvisited relay `j`
- update
  `dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + dist_imp[relay_i][relay_j])`

Final answer:

- after all relays are visited, add the shortest distance from the last relay
  to city `n`
- answer is
  `min(dp[(1 << k) - 1][i] + dist_imp[relay_i][finish])`

If this value is still infinity, print `-1`.

### 3. Why this is the intended viewpoint

This is **not** a Hamiltonian-path problem. Nadia is allowed to revisit roads
and cities. The hard part is only choosing the order in which the relay cities
are covered.

## Complexity
- Let `I = k + 2` be the number of important cities.
- Dijkstra from each important city:
  **O(I \cdot m \log n)**
- Bitmask DP:
  **O(k^2 \cdot 2^k)**
- Total:
  **O((k + 2) \cdot m \log n + k^2 \cdot 2^k)**
- Space:
  **O(n + m + k \cdot 2^k)**

## Common Pitfalls
- Treating the task like a Hamiltonian path. Intermediate cities may be reused.
- Using 32-bit integers. Distances can be much larger than `2^31 - 1`.
- Forgetting disconnected graphs. Some important cities may be unreachable.
- Trying Floyd–Warshall on all `n` cities, which is far too slow.

## Example Walkthrough
For Sample 1:

- Start: `1`
- Relays: `3`, `5`
- Finish: `6`

Relevant shortest distances:

- `d(1, 3) = 2`
- `d(1, 5) = 7`
- `d(3, 5) = 5`
- `d(3, 6) = 6`
- `d(5, 6) = 1`

DP states:

- `dp[01][3] = 2`
- `dp[10][5] = 7`

Visit both relays:

- `dp[11][5] = 2 + 5 = 7`
- `dp[11][3] = 7 + 5 = 12`

Finish at city `6`:

- ending from `5`: `7 + 1 = 8`
- ending from `3`: `12 + 6 = 18`

So the minimum answer is `8`.

## Alternative Approaches
- If all roads had weight `1`, BFS could replace Dijkstra.
- Brute-forcing all relay visit orders costs `O(k! \cdot k)` and is too slow.
- The same DP idea also works if city `1` is included as a dummy checkpoint,
  but the state definitions become slightly less clean.
