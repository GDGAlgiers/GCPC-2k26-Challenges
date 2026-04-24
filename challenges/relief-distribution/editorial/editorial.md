# Relief Distribution — Editorial

## Tags
`greedy` `sorting` `priority_queue`

## Key Observation
> Processing boxes in increasing order of deadline allows us to maintain a feasible set of deliveries up to the current day. When the number of selected boxes exceeds the current deadline, removing the heaviest box minimises the total weight without sacrificing the maximum possible count.

## Approach
1. **Sort by deadline**  
   Sort all boxes by their expiry deadline in ascending order. This ensures we consider the most urgent boxes first and never miss a chance to schedule a box that would expire soon.

2. **Maintain a max‑heap of selected weights**  
   Iterate through the sorted boxes. For each box, add its weight to a max‑heap (implemented as a min‑heap with negative values).  
   If the size of the heap exceeds the current box's deadline, it means we have selected more boxes than the number of days available up to that deadline. To keep the schedule feasible and minimise total weight, pop the **largest** weight from the heap.

3. **Extract the final answer**  
   After processing all boxes, the heap contains the optimal set of deliveries. The number of boxes is the heap size, and the total weight is the sum of its elements.

## Complexity
- **Time:** $O(N \log N)$ — sorting takes $O(N \log N)$ and each heap operation is $O(\log N)$.
- **Space:** $O(N)$ — for storing the boxes and the heap.

## Common Pitfalls
- **Sorting by weight first** — this fails to respect urgency and may schedule a light box too late.
- **Using a min‑heap and popping the smallest weight** — this maximises total weight instead of minimising it.
- **Forgetting that the deadline limits the number of selected boxes** — the condition is `heap.size() > d`, not `heap.size() > current_day`.
- **Integer overflow** — total weight can be up to $N \times 10^4 = 10^9$, which fits in a 32‑bit signed integer, but use `long long` in C++ for safety.

## Example Walkthrough
**Sample Input:**
```
5
3 2
7 1
4 3
5 4
2 1
```

**Step 1: Sort by deadline**

| Deadline | Weight |
|----------|--------|
| 1        | 7      |
| 1        | 2      |
| 2        | 3      |
| 3        | 4      |
| 4        | 5      |

**Step 2: Process each box with a max‑heap (shown as positive values for clarity)**

- **Box (d=1, w=7):** heap = [7], size = 1 ≤ 1 → keep.
- **Box (d=1, w=2):** heap = [7, 2], size = 2 > 1 → pop max (7), heap = [2].
- **Box (d=2, w=3):** heap = [2, 3], size = 2 ≤ 2 → keep.
- **Box (d=3, w=4):** heap = [2, 3, 4], size = 3 ≤ 3 → keep.
- **Box (d=4, w=5):** heap = [2, 3, 4, 5], size = 4 ≤ 4 → keep.

**Step 3: Result**  
Heap = [2, 3, 4, 5] → **4 boxes**, total weight = **14**.

## Alternative Approaches
- **Dynamic Programming**  
  $dp[i][j]$ = minimum weight to schedule $j$ boxes from the first $i$ boxes. Complexity $O(N \cdot \max(d_i))$, which is too slow for $N=10^5$.
- **Brute Force / Backtracking**  
  Try all subsets of boxes and check feasibility. Exponential time, only works for very small $N$.
- **Greedy without heap (using a balanced BST)**  
  Same logic but with explicit removal of the maximum; equivalent complexity.
