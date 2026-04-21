// Reference solution for "The Sarrus Oracle".
//
// Theory:
// - Every prime p satisfies 2^p == 2 (mod p).
// - Some composite numbers satisfy it as well.
// - The problem asks us to count only those composite false positives.
//
// Strategy:
// 1. Read all interval queries and find the largest R.
// 2. Sieve all primes up to that limit.
// 3. For every composite n, test whether 2^n mod n == 2.
// 4. Build prefix sums and answer every query in O(1).

package main

import (
	"bufio"
	"fmt"
	"os"
)

func modPow(base, exp, mod int64) int64 {
	// Binary exponentiation under a modulus.
	result := int64(1 % mod)
	cur := base % mod
	for exp > 0 {
		if exp&1 == 1 {
			result = (result * cur) % mod
		}
		cur = (cur * cur) % mod
		exp >>= 1
	}
	return result
}

func main() {
	in := bufio.NewReaderSize(os.Stdin, 1<<20)
	out := bufio.NewWriterSize(os.Stdout, 1<<20)
	defer out.Flush()

	var q int
	if _, err := fmt.Fscan(in, &q); err != nil {
		return
	}

	left := make([]int, q)
	right := make([]int, q)
	maxR := 0

	// We need maxR before starting the sieve and prefix preprocessing.
	for i := 0; i < q; i++ {
		fmt.Fscan(in, &left[i], &right[i])
		if right[i] > maxR {
			maxR = right[i]
		}
	}

	// Sieve of Eratosthenes.
	prime := make([]bool, maxR+1)
	for i := 2; i <= maxR; i++ {
		prime[i] = true
	}
	for i := 2; i*i <= maxR; i++ {
		if prime[i] {
			for j := i * i; j <= maxR; j += i {
				prime[j] = false
			}
		}
	}

	// prefix[n] = number of Sarrus numbers in [2, n].
	prefix := make([]int, maxR+1)
	count := 0
	for n := 2; n <= maxR; n++ {
		// Prime numbers satisfy the congruence too, but are excluded
		// by definition, so only composite numbers are counted.
		if !prime[n] && modPow(2, int64(n), int64(n)) == 2 {
			count++
		}
		prefix[n] = count
	}

	for i := 0; i < q; i++ {
		// Standard prefix-sum interval query.
		fmt.Fprintln(out, prefix[right[i]]-prefix[left[i]-1])
	}
}
