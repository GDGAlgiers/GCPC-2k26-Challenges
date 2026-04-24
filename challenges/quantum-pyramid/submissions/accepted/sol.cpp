#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// A structure to hold the classical bits and the qubit state
struct Node {
    long long c;
    int q; // 0, 1, or 2 (for superposition '=')
};

// The associative merge operation representing the pyramid rules
Node mergeNodes(const Node& a, const Node& b) {
    if (a.c > b.c) return a;
    if (a.c < b.c) return b;
    if (a.q == b.q) return a;
    return {a.c, 2}; // Superposition
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, Q;
    if (!(cin >> n >> Q)) return 0;

    // We need up to log2(100000) ~ 16, 18 is safe.
    int maxLog = log2(n) + 2;
    vector<vector<Node>> st(maxLog, vector<Node>(n + 1));

    // Read input and initialize the base of the sparse table
    for (int i = 1; i <= n; i++) {
        long long a;
        cin >> a;
        st[0][i] = {a / 2, (int)(a % 2)};
    }

    // Build the Sparse Table
    for (int p = 1; (1 << p) <= n; p++) {
        for (int i = 1; i + (1 << p) - 1 <= n; i++) {
            st[p][i] = mergeNodes(st[p - 1][i], st[p - 1][i + (1 << (p - 1))]);
        }
    }

    // Process queries
    for (int q = 0; q < Q; q++) {
        int k, r;
        cin >> k >> r;

        // The range of inputs that eventually combine into this register
        // starts at index k and has length r (so it ends at k + r - 1).
        int L = k;
        int R = k + r - 1;

        // Using O(1) Sparse Table range query
        int p = log2(R - L + 1);
        Node res = mergeNodes(st[p][L], st[p][R - (1 << p) + 1]);

        long long base_val = res.c * 2;

        if (res.q == 0) {
            cout << base_val << "\n";
        } else if (res.q == 1) {
            cout << base_val + 1 << "\n";
        } else {
            // Superposition outputs both possibilities in increasing order
            cout << base_val << " " << base_val + 1 << "\n";
        }
    }

    return 0;
}
