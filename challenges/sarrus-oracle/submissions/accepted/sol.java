/*
 * Reference solution for "The Sarrus Oracle".
 *
 * Theory:
 * - Every prime p satisfies 2^p == 2 (mod p).
 * - Some composite numbers satisfy it too; those are the false positives.
 * - The problem asks us to count those composite false positives over ranges.
 *
 * Strategy:
 * 1. Read all queries and compute maxR.
 * 2. Sieve all primes up to maxR.
 * 3. For each composite n, test whether 2^n mod n == 2.
 * 4. Build prefix sums so each interval answer is O(1).
 */

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.PrintWriter;

public class sol {
    private static long modPow(long base, long exp, long mod) {
        // Binary exponentiation under a modulus.
        long result = 1 % mod;
        long cur = base % mod;
        while (exp > 0) {
            if ((exp & 1L) != 0) {
                result = (result * cur) % mod;
            }
            cur = (cur * cur) % mod;
            exp >>= 1;
        }
        return result;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);

        int q = fs.nextInt();
        int[] left = new int[q];
        int[] right = new int[q];
        int maxR = 0;

        // Read queries first because preprocessing depends on the largest R.
        for (int i = 0; i < q; i++) {
            left[i] = fs.nextInt();
            right[i] = fs.nextInt();
            if (right[i] > maxR) {
                maxR = right[i];
            }
        }

        // Sieve of Eratosthenes.
        boolean[] prime = new boolean[maxR + 1];
        for (int i = 2; i <= maxR; i++) {
            prime[i] = true;
        }
        for (int i = 2; (long) i * i <= maxR; i++) {
            if (prime[i]) {
                for (int j = i * i; j <= maxR; j += i) {
                    prime[j] = false;
                }
            }
        }

        // prefix[n] counts Sarrus numbers in [2, n].
        int[] prefix = new int[maxR + 1];
        int count = 0;
        for (int n = 2; n <= maxR; n++) {
            // We only count composite numbers that satisfy the congruence.
            if (!prime[n] && modPow(2L, n, n) == 2L) {
                count++;
            }
            prefix[n] = count;
        }

        for (int i = 0; i < q; i++) {
            // Answer [L, R] by subtracting prefix sums.
            out.println(prefix[right[i]] - prefix[left[i] - 1]);
        }

        out.flush();
    }

    private static class FastScanner {
        private final BufferedInputStream in = new BufferedInputStream(System.in);
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) {
                    return -1;
                }
            }
            return buffer[ptr++];
        }

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);

            long sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            long value = 0;
            while (c > ' ') {
                value = value * 10 + (c - '0');
                c = read();
            }
            return value * sign;
        }

        int nextInt() throws IOException {
            return (int) nextLong();
        }
    }
}
