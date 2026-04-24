# Hoggar Trail — Editorial

## Tags
`dynamic programming` `combinatorics` `segment tree` `BIT` `coordinate compression`

## Key Observation
> For any pair of indices $i < j$, the number of subsequences where $a_i$ and $a_j$ are **consecutive** elements is $2^{i-1} \cdot 2^{n-j}$ (any subset of elements before $i$, all elements strictly between $i$ and $j$ must be excluded, any subset of elements after $j$). The total answer is therefore:
> $$\sum_{i < j} |a_i - a_j| \cdot 2^{i-1} \cdot 2^{n-j}$$

## Approach

1. **Reformulate the sum.** Reindex to 0-based. For each pair $(i, j)$ with $i < j$, the contribution is $|a_i - a_j| \cdot 2^i \cdot 2^{n-j-1}$. Factor out $2^{n-j-1}$ to get:
   $$\text{ans} = \sum_{j=0}^{n-1} 2^{n-j-1} \cdot \sum_{i < j} |a_i - a_j| \cdot 2^i$$

2. **Process left to right.** For each position $j$, we need:
   $$S_j = \sum_{i < j} |a_i - a_j| \cdot 2^i = \underbrace{\sum_{\substack{i<j \\ a_i < a_j}} (a_j - a_i) \cdot 2^i}_{\text{left part}} + \underbrace{\sum_{\substack{i<j \\ a_i > a_j}} (a_i - a_j) \cdot 2^i}_{\text{right part}}$$

3. **Use a Fenwick tree (BIT) / segment tree on coordinate-compressed values.** Maintain two arrays indexed by compressed rank:
   - `cnt[r]` = sum of $2^i$ for all previously processed indices $i$ where $a_i$ maps to rank $r$.
   - `sum[r]` = sum of $a_i \cdot 2^i$ for all previously processed indices $i$ where $a_i$ maps to rank $r$.

   Then for each $j$ with value $x = a_j$:
   - Left query (ranks < rank of $x$): contribution = $x \cdot \text{cnt\_prefix} - \text{sum\_prefix}$
   - Right query (ranks > rank of $x$): contribution = $\text{sum\_suffix} - x \cdot \text{cnt\_suffix}$
   - Total $S_j$ = left + right; add $S_j \cdot 2^{n-j-1}$ to the answer.
   - Update the structure: insert rank of $x$ with weight $2^j$ and value $a_j \cdot 2^j$.

4. **Coordinate compress** all $a_i$ values first (there are at most $n$ distinct values, so the rank range is $[1, n]$), then run the above sweep.

## Complexity
- **Time:** $O(n \log n)$
- **Space:** $O(n)$

## Common Pitfalls
- **Integer overflow** — all arithmetic must be done modulo $10^9 + 7$. Use `long long` in C++.
- **Negative values** — the values $a_i$ can be negative; always coordinate-compress, never directly index by value.
- **Off-by-one in powers** — be careful whether powers are indexed from $0$ or $1$.
- **Modular subtraction** — when computing $a - b$ mod $p$, use `((a - b) % p + p) % p` to avoid negative results.

## Example Walkthrough

For `[2, 7, 5]` ($n = 3$), the 0-based formula gives:

| Pair | Contribution |
|------|-------------|
| $(0,1)$: $\|2-7\|=5$ | $5 \cdot 2^0 \cdot 2^{3-1-1} = 5 \cdot 1 \cdot 2 = 10$ |
| $(0,2)$: $\|2-5\|=3$ | $3 \cdot 2^0 \cdot 2^{3-2-1} = 3 \cdot 1 \cdot 1 = 3$ |
| $(1,2)$: $\|7-5\|=2$ | $2 \cdot 2^1 \cdot 2^{3-2-1} = 2 \cdot 2 \cdot 1 = 4$ |

Total: $10 + 3 + 4 = 17$. ✓

## Alternative Approaches
- **Brute force** $O(n^2)$: enumerate all pairs, multiply by $2^{i} \cdot 2^{n-j-1}$, take mod. Passes for $n \le 10^4$.
- **Merge-sort based**: similar to counting inversions, you can split contributions along a divide-and-conquer step, but the BIT approach is simpler to implement.
