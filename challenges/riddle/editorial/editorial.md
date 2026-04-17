# Permutation Riddle — Editorial

## Tags

`dp` `bitmasks` `graphs`

## Key Observation

> Notice that we can represent our numbers as nodes of a graph, we can assign an edge between all pairs of nodes that can be adjacent in a valid permutation (for all $u,v \in \{1,2,\cdots,n\}, u \neq v$, an edge $(u,v)$ exists iff $\left| u - v  \right| \le d$), the problem then reduces to finding the count of all hamiltonian paths in this graph, which is a standard problem.

## Approach

1. **Base Case Initialization**: We initialize our DP table $dp[2^n][n]$ with zeros. For every element $i \in \{0, \dots, n-1\}$, we set $dp[1 \ll i][i] = 1$. This represents starting a permutation with any single number from the set $\{1, \dots, n\}$.
2. **DP Transitions**: We iterate through every bitmask from $1$ to $2^n - 1$. For each state where $dp[mask][i] > 0$ (meaning a valid partial permutation exists using the set `mask` and ending at $i$):
   * We look for the next element $j$ to add.
   * $j$ must not be in the current mask: `!(mask & (1 << j))`.
   * $j$ must satisfy the distance constraint with the previous element $i$: $|i - j| \le d$.
   * If both conditions are met, we update the new state: $dp[mask | (1 \ll j)][j] = (dp[mask | (1 \ll j)][j] + dp[mask][i]) \pmod{10^9+7}$.
3. **Step three — how you extract the final answer**: Once all masks are processed, the final answer is the sum of $dp[(1 \ll n) - 1][i]$ for all $0 \le i < n$. This sum represents all permutations that have visited every node exactly once, regardless of which node they ended on.

## Complexity

- **Time:** $O(2^n \cdot n \cdot d)$. There are $2^n \cdot n$ total states. By precomputing an adjacency mask, we only check the $2d$ possible neighbors for each state, ensuring it stays within the 2s time limit.
- **Space:** $O(2^n \cdot n)$ to store the DP table. For $n=20$, this is roughly 80–160 MB, fitting within the 256 MB limit.

## Common Pitfalls

- **Integer Overflow**: Use `long long` for the DP table and the summation. The number of paths can be massive, so the modulo $10^9+7$ must be applied at every addition.
- **Off-by-one errors**: Mapping the problem's 1-indexed values to 0-indexed bit positions requires careful handling of indices $i$ and $i+1$.
- **Adjacency Checks**: A common mistake is checking all $n$ nodes for every state. Precomputing the `adj_mask` or restricting the inner loop to $i-d$ to $i+d$ is necessary to stay under the time limit.

## Example Walkthrough

**Sample Input 1 ($n=4, d=2$):**
- **Nodes**: $\{1, 2, 3, 4\}$.
- **Edges**: (1,2), (1,3), (2,3), (2,4), (3,4). (e.g., 1 is not connected to 4 because $|4-1|=3 > 2$).
- **Base Cases**: `dp[1][0]=1`, `dp[2][1]=1`, `dp[4][2]=1`, `dp[8][3]=1`.
- **Transitions**: From `dp[1][0]` (permutation `[1]`), we can move to 2 (mask 3) or 3 (mask 5).
- **Valid Full Path**: `[1, 2, 4, 3]` corresponds to the transition sequence: 
  `dp[1][0] -> dp[3][1] -> dp[11][3] -> dp[15][2]`.
- **Final Result**: Summing all $dp[15][i]$ for $i \in \{0, 1, 2, 3\}$ yields 12.

## Alternative Approaches

- **Memoization (Top-Down)**: Using a recursive function `solve(mask, last)` with a memoization table. This is often easier to implement and only visits reachable states.
- **Backtracking**: Brute force $O(n!)$ would only pass for $n \le 11$. For $n=20$, the bitmask DP approach is the only viable path.
- **Connected Component DP**: This is an advanced kind of dynamic programming that can solve this problem more efficiently, I recommend reading about this.