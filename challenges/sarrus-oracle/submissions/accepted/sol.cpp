// Reference solution for "The Sarrus Oracle".
//
// Theory:
// - Every prime p satisfies 2^p == 2 (mod p).
// - Some composite numbers satisfy the same congruence too.
// - Those composite false positives are exactly the numbers we count.
//
// Plan:
// 1. Read all queries and find the largest right endpoint.
// 2. Sieve all primes up to that value.
// 3. For each composite n, test whether 2^n mod n == 2.
// 4. Build a prefix sum so each interval answer becomes O(1).

#include <bits/stdc++.h>
using namespace std;

int mod_pow(int base, int exp, int mod) {
    // Binary exponentiation:
    // repeatedly square the base and reduce modulo mod after each step.
    long long result = 1 % mod;
    long long cur = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * cur) % mod;
        }
        cur = (cur * cur) % mod;
        exp >>= 1;
    }
    return static_cast<int>(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    vector<pair<int, int>> queries(q);
    int max_r = 0;
    for (auto &query : queries) {
        cin >> query.first >> query.second;
        max_r = max(max_r, query.second);
    }

    // Sieve of Eratosthenes: prime[n] tells us whether n is prime.
    vector<char> prime(max_r + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; 1LL * i * i <= max_r; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= max_r; j += i) {
                prime[j] = false;
            }
        }
    }

    // prefix[i] = number of Sarrus numbers in [2, i].
    vector<int> prefix(max_r + 1, 0);
    int count = 0;
    for (int n = 2; n <= max_r; ++n) {
        // Prime numbers also satisfy the congruence, but the definition only
        // counts composite ones, so we check !prime[n] first.
        if (!prime[n] && mod_pow(2, n, n) == 2) {
            ++count;
        }
        prefix[n] = count;
    }

    for (const auto &[left, right] : queries) {
        // Standard prefix-sum interval extraction.
        cout << prefix[right] - prefix[left - 1] << '\n';
    }
    return 0;
}
