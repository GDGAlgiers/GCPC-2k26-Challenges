# Latency Budget — Editorial

## Tags
`dynamic programming` `knapsack` `counting` `recursion`

## Key Observation
> Since $N \leq 10$, $k_i \leq 10$, and $B \leq 1000$, we can either use recursion to try all combinations with pruning, or a simple DP where $dp[b]$ counts the number of ways to reach exactly sum $b$. Both approaches are fast enough under the reduced constraints.

## Approach

1. **Choose your method:** The constraints are small enough that even a naive recursive backtracking solution (pruning when sum exceeds $B$) will pass. For an efficient solution, use counting knapsack DP.

2. **DP method:** Initialize $dp[0] = 1$ (one way to have sum $0$ before choosing any replica). For each service $i$, create a new array $ndp$ where $ndp[b] = \sum_{l \in replicas} dp[b - l]$ for all $b \geq l$. Then set $dp = ndp$ and move to the next service.

3. **Get the answer:** After processing all $N$ services, sum all $dp[0..B]$. This counts every combination whose total latency is at most $B$.

## Complexity

- **Time:** $O(N \cdot K \cdot B)$ with DP — at most $10 \times 10 \times 1000 = 100,000$ operations
- **Space:** $O(B)$ — two arrays of size $1001$ suffice

With brute force recursion: $O(K^N)$ worst case ($10^{10}$) but pruning makes it acceptable in practice for these constraints.

## Common Pitfalls

- **In-place DP update:** If you update $dp$ while iterating replicas of the same service, you'll count replicas multiple times (unbounded knapsack). Always write to a fresh $ndp$ array.
- **Budget boundary:** The condition is $\leq B$, not $< B$. Include index $B$ in your final sum.
- **Recursion depth:** With $N=10$ you're safe, but for completeness set recursion limit higher.
- **Input parsing:** Each service line starts with $k_i$ — don't treat it as a latency value.

## Example Walkthrough

**Input:**
```
3 40
3 10 20 15
2 5 30
3 8 12 25
```

**Step 1 — Initialize:** $dp = [1, 0, 0, ..., 0]$ (size 41)

**Step 2 — Service 0** (replicas 10, 20, 15):
- From $dp[0]=1$: add to positions 10, 20, 15
- Result: $dp[10]=1$, $dp[15]=1$, $dp[20]=1$

**Step 3 — Service 1** (replicas 5, 30):
- From $dp[10]$: $10+5=15$, $10+30=40$
- From $dp[15]$: $15+5=20$, $15+30=45$ (over budget, ignore)
- From $dp[20]$: $20+5=25$, $20+30=50$ (ignore)
- Result: counts at 15, 20, 25, 40 each become 1

**Step 4 — Service 2** (replicas 8, 12, 25):
- From sum 15: add to 23, 27, 40
- From sum 20: add to 28, 32 (45 over)
- From sum 25: add to 33, 37 (50 over)
- From sum 40: all exceed (48, 52, 65)
- Final non-zero within budget: 23, 27, 28, 32, 33, 37, 40 — each with count 1

**Step 5 — Sum:** $1+1+1+1+1+1+1 = 7$

## Alternative Approaches

- **Brute force recursion:** Try all $\prod k_i$ combinations recursively. With $k_i \leq 10$ and $N \leq 10$, worst case $10^{10}$ combinations is too many, but pruning when sum exceeds $B$ makes it feasible for most inputs. Good for beginners to implement first.

- **Meet-in-the-middle:** Split services into two halves ($N/2$ each), enumerate all sums from each half, sort one half, and for each sum in the other half count how many in the first half are $\leq B - sum$. Works for larger $B$ but overkill here.

- **Generating functions:** The answer is the coefficient sum of $\prod_{i=1}^N (\sum_{j=1}^{k_i} x^{l_{i,j}})$ for degrees $\leq B$. Uses polynomial multiplication but too advanced for an Easy problem.
