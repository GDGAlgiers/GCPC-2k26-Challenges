#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 100005
#define MAXQ 100005
#define HASH_SIZE 500009 // Prime number for hash table size

long long power2[MAXN];

// DSU Variables
int parent[MAXN];
int components;

int find_set(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find_set(parent[i]);
}

void unite_sets(int i, int j) {
    int root_i = find_set(i);
    int root_j = find_set(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
        components--;
    }
}

// Custom Hash Table to act as std::set<pair<int, int>>
int head[HASH_SIZE];
int next_node[MAXQ * 2];
int val_r[MAXQ * 2];
int val_c[MAXQ * 2];
int node_cnt = 0;

int hash_func(int r, int c) {
    long long h = r;
    h = (h * 31337 + c) % HASH_SIZE;
    if (h < 0) h += HASH_SIZE;
    return (int)h;
}

int is_occupied(int r, int c) {
    int h = hash_func(r, c);
    for (int i = head[h]; i != -1; i = next_node[i]) {
        if (val_r[i] == r && val_c[i] == c) {
            return 1; // Found
        }
    }
    return 0; // Not found
}

void mark_occupied(int r, int c) {
    int h = hash_func(r, c);
    next_node[node_cnt] = head[h];
    val_r[node_cnt] = r;
    val_c[node_cnt] = c;
    head[h] = node_cnt++;
}

int main() {
    int N, M, Q;
    
    // Read input, stop if EOF
    if (scanf("%d %d %d", &N, &M, &Q) != 3) {
        return 0;
    }

    // Precompute powers of 2 for O(1) configuration calculation 
    power2[0] = 1;
    for (int i = 1; i <= N; i++) {
        power2[i] = (power2[i - 1] * 2) % MOD;
    }

    // Initialize DSU
    components = N;
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    // Initialize Hash Table (fill heads with -1 to indicate empty)
    memset(head, -1, sizeof(head));

    for (int i = 0; i < Q; i++) {
        int r1, c1, r2, c2;
        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

        // Check if either hole is already occupied
        if (is_occupied(r1, c1) || is_occupied(r2, c2)) {
            // Discard cable, output current configuration
            printf("%lld\n", power2[components]);
        } else {
            // Mark holes as occupied and connect columns
            mark_occupied(r1, c1);
            mark_occupied(r2, c2);
            unite_sets(c1, c2);
            printf("%lld\n", power2[components]);
        }
    }

    return 0;
}
