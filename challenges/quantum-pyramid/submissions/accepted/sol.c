#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// A structure to hold the classical bits and the qubit state
typedef struct {
    long long c;
    int q; // 0, 1, or 2 (for superposition '=')
} Node;

// The associative merge operation representing the pyramid rules
Node mergeNodes(Node a, Node b) {
    if (a.c > b.c) return a;
    if (a.c < b.c) return b;
    if (a.q == b.q) return a;
    
    Node res;
    res.c = a.c;
    res.q = 2; // Superposition
    return res;
}

int main() {
    int n, Q;
    if (scanf("%d %d", &n, &Q) != 2) return 0;

    // We need up to log2(100000) ~ 16, 18 is safe.
    int maxLog = (int)log2(n) + 2;
    
    // Allocate 2D array for the sparse table
    Node** st = (Node**)malloc(maxLog * sizeof(Node*));
    for (int i = 0; i < maxLog; i++) {
        st[i] = (Node*)malloc((n + 1) * sizeof(Node));
    }

    // Read input and initialize the base of the sparse table
    for (int i = 1; i <= n; i++) {
        long long a;
        scanf("%lld", &a);
        st[0][i].c = a / 2;
        st[0][i].q = (int)(a % 2);
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
        scanf("%d %d", &k, &r);

        // The range of inputs that eventually combine into this register
        // starts at index k and has length r (so it ends at k + r - 1).
        int L = k;
        int R = k + r - 1;

        // Using O(1) Sparse Table range query
        int p = (int)log2(R - L + 1);
        Node res = mergeNodes(st[p][L], st[p][R - (1 << p) + 1]);

        long long base_val = res.c * 2;

        if (res.q == 0) {
            printf("%lld\n", base_val);
        } else if (res.q == 1) {
            printf("%lld\n", base_val + 1);
        } else {
            // Superposition outputs both possibilities in increasing order
            printf("%lld %lld\n", base_val, base_val + 1);
        }
    }

    // Free allocated memory
    for (int i = 0; i < maxLog; i++) {
        free(st[i]);
    }
    free(st);

    return 0;
}
