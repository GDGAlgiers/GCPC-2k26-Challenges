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

	var N, W, X, C int
	fmt.Fscan(reader, &N, &W, &X, &C)

	var E int
	fmt.Fscan(reader, &E)

	failures := make([][]int, N)
	for i := range failures {
		failures[i] = []int{}
	}

	for i := 0; i < E; i++ {
		var T, S, R int
		fmt.Fscan(reader, &T, &S, &R)
		if R == 0 {
			failures[S] = append(failures[S], T)
		}
	}

	type Interval struct{ open, close int }
	intervals := make([][]Interval, N)

	for s := 0; s < N; s++ {
		fl := failures[s]
		skipUntil := -1
		valid := []int{}

		for i := 0; i < len(fl); i++ {
			t := fl[i]
			if t < skipUntil {
				continue
			}
			valid = append(valid, t)
			for len(valid) > 0 && valid[0] < t-W {
				valid = valid[1:]
			}
			if len(valid) == X {
				openTime := t
				closeTime := openTime + C
				intervals[s] = append(intervals[s], Interval{openTime, closeTime})
				skipUntil = closeTime
				valid = []int{}
			}
		}
	}

	var Q int
	fmt.Fscan(reader, &Q)

	for i := 0; i < Q; i++ {
		var T, S int
		fmt.Fscan(reader, &T, &S)
		ivs := intervals[S]
		lo, hi := 0, len(ivs)-1
		found := false
		for lo <= hi {
			mid := (lo + hi) / 2
			if ivs[mid].open <= T {
				if ivs[mid].close > T {
					found = true
					break
				}
				lo = mid + 1
			} else {
				hi = mid - 1
			}
		}
		if found {
			fmt.Fprintln(writer, "OPEN")
		} else {
			fmt.Fprintln(writer, "CLOSED")
		}
	}
}
