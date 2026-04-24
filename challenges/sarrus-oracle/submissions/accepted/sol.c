/* Reference solution for "The Sarrus Oracle".
 *
 * Theory:
 * - Every prime p satisfies 2^p == 2 (mod p).
 * - Some composite numbers also satisfy that congruence.
 * - Only those composite false positives are counted.
 *
 * We therefore precompute, for every n up to the largest query bound,
 * whether n is a Sarrus number, then build prefix sums over that array.
 */

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod) {
    /* Binary exponentiation under a modulus. */
    uint64_t result = 1 % mod;
    uint64_t cur = base % mod;
    while (exp > 0) {
        if (exp & 1ULL) {
            result = (result * cur) % mod;
        }
        cur = (cur * cur) % mod;
        exp >>= 1ULL;
    }
    return result;
}

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) {
        return 0;
    }

    int *left = (int *)malloc((size_t)q * sizeof(int));
    int *right = (int *)malloc((size_t)q * sizeof(int));
    int max_r = 0;

    /* Read queries first so we know how far preprocessing must go. */
    for (int i = 0; i < q; ++i) {
        if (scanf("%d %d", &left[i], &right[i]) != 2) {
            return 0;
        }
        if (right[i] > max_r) {
            max_r = right[i];
        }
    }

    unsigned char *prime = (unsigned char *)malloc((size_t)(max_r + 1));
    int *prefix = (int *)calloc((size_t)(max_r + 1), sizeof(int));
    if (prime == NULL || prefix == NULL || left == NULL || right == NULL) {
        return 0;
    }

    /* Sieve of Eratosthenes. */
    for (int i = 0; i <= max_r; ++i) {
        prime[i] = 1;
    }
    prime[0] = 0;
    prime[1] = 0;

    for (int i = 2; (int64_t)i * i <= max_r; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= max_r; j += i) {
                prime[j] = 0;
            }
        }
    }

    /* prefix[n] counts Sarrus numbers in [2, n]. */
    int count = 0;
    for (int n = 2; n <= max_r; ++n) {
        /* Prime numbers pass the congruence too, but must not be counted. */
        if (!prime[n] && mod_pow(2U, (uint64_t)n, (uint64_t)n) == 2U) {
            ++count;
        }
        prefix[n] = count;
    }

    for (int i = 0; i < q; ++i) {
        /* Interval answer from prefix sums. */
        printf("%d\n", prefix[right[i]] - prefix[left[i] - 1]);
    }

    free(prime);
    free(prefix);
    free(left);
    free(right);
    return 0;
}
