# DzNet Signal Coverage — Editorial

## Tags
`bitmask` `bruteforce` `graph`

## Key Observation
For each city, a tower has a fixed coverage set (itself + direct neighbors). Since `N <= 20`, we can enumerate all subsets of cities and choose the smallest subset whose union of coverage sets covers all cities.

## Approach
1. Read `N` and the `N x N` adjacency matrix.
2. Enumerate all subsets of cities from `0` to `(1 << N) - 1`.
3. For each subset, simulate placing towers in selected cities:
4. Mark each selected city and all its direct neighbors as covered.
5. If all cities are covered, minimize the selected tower count.

## Complexity
- **Time:** `O(2^N * N^2)`
- **Space:** `O(N)`

## Common Pitfalls
- Forgetting that a tower always covers its own city.
- Parsing the adjacency matrix with the wrong format.
- Trying to use this brute-force solution for `N` larger than 20.

## Example Walkthrough
For Sample 1 (`N=4`), city masks are:
- city 1 covers `{1,2}`
- city 2 covers `{1,2,3}`
- city 3 covers `{2,3,4}`
- city 4 covers `{3,4}`

No single city covers all 4 cities.
Choosing cities 2 and 3 covers all cities, so the minimum is `2`.
