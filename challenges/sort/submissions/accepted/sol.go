package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var n, k int
	fmt.Fscan(reader, &n, &k)

	a := make([]int, n)
	for i := range a {
		fmt.Fscan(reader, &a[i])
	}

	vec := []int{1}
	ans := 0

	for i := 1; i < n; i++ {
		if a[i]*2 > a[i-1] {
			vec[len(vec)-1]++
		} else {
			vec = append(vec, 1)
		}
	}

	for _, x := range vec {
		if x-k > 0 {
			ans += x - k
		}
	}

	fmt.Fprintln(writer, ans)
}
