"""
Reference solution for "The Sarrus Oracle".

Theory:
- Every prime p satisfies 2^p == 2 (mod p).
- Some composite numbers satisfy the same congruence too.
- Those composite false positives are the Sarrus numbers we count.

Algorithm:
1. Read all interval queries and find the largest right endpoint.
2. Sieve all primes up to that limit.
3. For each n in [2, limit]:
   - ignore it if it is prime
   - otherwise test whether 2^n mod n == 2
4. Build a prefix sum over all detected Sarrus numbers.
5. Answer each interval [L, R] with prefix[R] - prefix[L - 1].
"""

import math
import sys


def build_prefix(limit: int) -> list[int]:
    # Sieve of Eratosthenes: prime[n] is 1 iff n is prime.
    prime = bytearray(b"\x01") * (limit + 1)
    prime[0:2] = b"\x00\x00"

    for i in range(2, math.isqrt(limit) + 1):
        if prime[i]:
            start = i * i
            prime[start : limit + 1 : i] = b"\x00" * (((limit - start) // i) + 1)

    # prefix[i] = number of Sarrus numbers in [2, i].
    prefix = [0] * (limit + 1)
    count = 0
    for n in range(2, limit + 1):
        # Python's 3-argument pow performs fast modular exponentiation, so
        # this computes 2^n mod n without ever constructing the huge value 2^n.
        if not prime[n] and pow(2, n, n) == 2:
            count += 1
        prefix[n] = count

    return prefix


def main() -> None:
    # Read everything up front because the preprocessing limit depends on the
    # maximum right endpoint across all queries.
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    q = data[0]
    queries: list[tuple[int, int]] = []
    max_r = 0

    idx = 1
    for _ in range(q):
        left = data[idx]
        right = data[idx + 1]
        idx += 2
        queries.append((left, right))
        if right > max_r:
            max_r = right

    prefix = build_prefix(max_r)

    # Each answer is an interval count extracted from the prefix sums.
    out = [str(prefix[right] - prefix[left - 1]) for left, right in queries]
    sys.stdout.write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
