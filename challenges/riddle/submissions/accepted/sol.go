package main

import (
	"fmt"
	"math/bits"
)

func main() {
	var n, d int
	_, err := fmt.Scan(&n, &d)
	if err != nil {
		return
	}

	mod := int64(1e9 + 7)

	dp := make([][]int64, 1<<n)
	for i := range dp {
		dp[i] = make([]int64, n)
	}

	for i := 0; i < n; i++ {
		dp[1<<i][i] = 1
	}

	adj_mask := make([]int, n)
	for i := 0; i < n; i++ {
		for j := max(i-d, 0); j < i; j++ {
			adj_mask[i] |= (1 << j)
		}
		for j := min(i+d, n-1); j > i; j-- {
			adj_mask[i] |= (1 << j)
		}
	}

	for mask := 1; mask < (1<<n); mask++ {
		for i := 0; i < n; i++ {
			if (mask&(1<<i)) == 0 || dp[mask][i] == 0 {
				continue
			}
			cur := uint(adj_mask[i] & (^mask))
			for cur > 0 {
				idx := bits.TrailingZeros(cur)
				next_mask := mask | (1 << idx)
				dp[next_mask][idx] = (dp[next_mask][idx] + dp[mask][i]) % mod
				cur ^= (1 << idx)
			}
		}
	}

	var ans int64 = 0
	full_mask := (1 << n) - 1
	for i := 0; i < n; i++ {
		ans = (ans + dp[full_mask][i]) % mod
	}
	fmt.Println(ans)
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}