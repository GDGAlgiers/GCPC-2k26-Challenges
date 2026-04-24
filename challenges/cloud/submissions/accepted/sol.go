package main
import "fmt"

func sz(n, k int64) int64 {
	if k > n { return 0 }
	if n == 1 { return 1 }
	if n%2 == 0 { return 2 * sz(n/2, k) }
	return 1 + 2*sz(n/2, k)
}

func f(n, k int64) int64 {
	if k > n { return 0 }
	if n == 1 { return 1 }
	if n%2 == 0 { return 2*f(n/2, k) + (n/2)*sz(n/2, k) }
	m := (n + 1) / 2
	return m + 2*f(n/2, k) + m*sz(n/2, k)
}

func main() {
	var n, k, N, K int64
	fmt.Scan(&n, &k, &N, &K)
	r, h := f(n, k), f(N, K)
	if r > h { fmt.Println("Raouf") } else if r < h { fmt.Println("Hachem") } else { fmt.Println("Tie") }
}