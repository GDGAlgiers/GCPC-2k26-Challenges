package main

import (
	"bufio"
	"fmt"
	"math/bits"
	"os"
)

// Node represents the classical bits and the qubit state
type Node struct {
	c int64
	q int // 0, 1, or 2 (for superposition '=')
}

// mergeNodes performs the associative merge operation representing the pyramid rules
func mergeNodes(a, b Node) Node {
	if a.c > b.c {
		return a
	}
	if a.c < b.c {
		return b
	}
	if a.q == b.q {
		return a
	}
	return Node{c: a.c, q: 2} // Superposition
}

func main() {
	// Use buffered I/O for performance
	reader := bufio.NewReader(os.Stdin)
	writer := bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var n, Q int
	if _, err := fmt.Fscan(reader, &n, &Q); err != nil {
		return
	}

	// Calculate maxLog using bit manipulation (equivalent to log2)
	maxLog := bits.Len(uint(n))
	st := make([][]Node, maxLog)
	for i := range st {
		st[i] = make([]Node, n+1)
	}

	// Read input and initialize the base of the sparse table (level 0)
	for i := 1; i <= n; i++ {
		var a int64
		fmt.Fscan(reader, &a)
		st[0][i] = Node{c: a / 2, q: int(a % 2)}
	}

	// Build the Sparse Table
	for p := 1; (1 << p) <= n; p++ {
		for i := 1; i+(1<<p)-1 <= n; i++ {
			st[p][i] = mergeNodes(st[p-1][i], st[p-1][i+(1<<(p-1))])
		}
	}

	// Process queries
	for q := 0; q < Q; q++ {
		var k, r int
		fmt.Fscan(reader, &k, &r)

		// Range [L, R]
		L := k
		R := k + r - 1

		// Standard Sparse Table O(1) query
		// bits.Len(x) - 1 is effectively floor(log2(x))
		p := bits.Len(uint(R-L+1)) - 1
		res := mergeNodes(st[p][L], st[p][R-(1<<p)+1])

		baseVal := res.c * 2

		switch res.q {
		case 0:
			fmt.Fprintln(writer, baseVal)
		case 1:
			fmt.Fprintln(writer, baseVal+1)
		default:
			// Superposition outputs both possibilities
			fmt.Fprintf(writer, "%d %d\n", baseVal, baseVal+1)
		}
	}
}