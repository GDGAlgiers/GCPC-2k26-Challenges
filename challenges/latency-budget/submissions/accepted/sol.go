// Accepted solution — Go
package main

import (
	"bufio"
	"fmt"
	"os"
)

var reader *bufio.Reader
var writer *bufio.Writer

func main() {
	reader = bufio.NewReader(os.Stdin)
	writer = bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var N, B int
	fmt.Fscan(reader, &N, &B)

	dp := make([]int64, B+1)
	dp[0] = 1

	for i := 0; i < N; i++ {
		var k int
		fmt.Fscan(reader, &k)
		replicas := make([]int, k)
		for j := 0; j < k; j++ {
			fmt.Fscan(reader, &replicas[j])
		}

		ndp := make([]int64, B+1)
		for _, latency := range replicas {
			for b := latency; b <= B; b++ {
				ndp[b] += dp[b-latency]
			}
		}
		dp = ndp
	}

	var ans int64
	for _, v := range dp {
		ans += v
	}
	fmt.Fprintln(writer, ans)
}
