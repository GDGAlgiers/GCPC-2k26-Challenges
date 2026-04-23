# Rassim Sort — Editorial

## Tags
`greedy` `math` `two-pointers` `implementation`

## Key Observation
> The global inequality $2^0 \cdot a_i < 2^1 \cdot a_{i+1} < \dots < 2^k \cdot a_{i+k}$ can be simplified into a purely local condition between adjacent elements: $a_{j-1} < 2 \cdot a_j$. Therefore, the answer is determined by finding the lengths of all contiguous segments that satisfy this local property.

## Approach
1. **Simplify the condition:** Start by breaking down the main inequality. For any two adjacent elements in the valid sequence, $2^x \cdot a_j < 2^{x+1} \cdot a_{j+1}$. Dividing both sides by $2^x$ yields $a_j < 2 \cdot a_{j+1}$. This means we only need to check if each element is strictly less than twice the element that follows it.
2. **Group into contiguous segments:** Iterate through the array starting from the second element. Keep track of the current sequence of valid adjacent pairs. If the condition $2 \cdot a_i > a_{i-1}$ holds, the current segment grows. If it breaks, record the length of the current segment and start a new one of length 1. 
3. **Extract the answer:** For each valid contiguous segment of length $L$, the number of valid subarrays of length $k+1$ it can produce is exactly $L - k$. If $L \le k$, it produces 0. We simply sum $\max(L - k, 0)$ across all recorded segment lengths to get the final answer.

## Complexity
- **Time:** $\mathcal{O}(n)$ — We iterate through the array exactly once to build the segment lengths, and then iterate through the segment list (which is at most size $n$) to sum the answers.
- **Space:** $\mathcal{O}(n)$ — For storing the original array and the `vec` array containing the lengths of valid segments.

## Common Pitfalls
- **Misinterpreting the subarray length:** The problem requires a subarray of length $k+1$ (from $a_i$ to $a_{i+k}$), not $k$. 
- **Integer overflow:** While the provided solution uses standard integers, computing $a_i \cdot 2$ could cause an overflow if elements approach the maximum 32-bit integer limit. Using `long long` for elements or rearranging the condition to $a_{i-1} / 2 < a_i$ (handling parity carefully) avoids this in edge cases.
- **Off-by-one errors:** Calculating the number of valid subarrays within a segment of length $L$ can easily cause an off-by-one bug. The correct formula is $L - k$, not $L - k + 1$, because $k$ represents the number of "steps" or "gaps" between the $k+1$ elements.

## Example Walkthrough
Let's walk through Sample Input 1:
`n = 4`, `k = 2`, and array `a = [1, 10, 100, 1000]`.

- **Initialize:** `vec = [1]`.
- **Index $i = 1$ ($a_1 = 10$):** Check $2 \cdot 10 > 1$. True. Segment grows. `vec = [2]`.
- **Index $i = 2$ ($a_2 = 100$):** Check $2 \cdot 100 > 10$. True. Segment grows. `vec = [3]`.
- **Index $i = 3$ ($a_3 = 1000$):** Check $2 \cdot 1000 > 100$. True. Segment grows. `vec = [4]`.

After the loop, we have one maximal segment of length $L = 4$.
We calculate the valid subarrays using our formula: $\max(4 - 2, 0) = 2$. 
The final output is **2**.

## Alternative Approaches
- **Sliding Window / Two Pointers:** Instead of explicitly storing the lengths of all segments in an auxiliary vector, you can maintain a sliding window $[L, R]$. Expand $R$ as long as the condition holds. Once $R - L = k$, increment your answer and advance $L$ to $L + 1$. This optimizes the space complexity to $\mathcal{O}(1)$ auxiliary space.
- **Prefix Sums on Booleans:** Create a boolean array `B` where $B[i] = 1$ if $a_{i-1} < 2 \cdot a_i$, and $B[i] = 0$ otherwise. Build a prefix sum array over `B`. A subarray ending at index $i$ and starting at $i-k$ is valid if the sum of `B` in that range is exactly $k$. This takes $\mathcal{O}(n)$ time and $\mathcal{O}(n)$ space.