#include <iostream>
#include <vector>
#include <set>

using namespace std;

/**
 * Problem: Arduino Breadboard Setup
 * Goal: Track connected electrical components and occupied holes.
 */

long long power2[100005];
const int MOD = 1e9 + 7;

struct DSU {
    vector<int> parent;
    int components;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        components = n;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            components--;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return 0;

    // Precompute powers of 2 for O(1) configuration calculation 
    power2[0] = 1;
    for (int i = 1; i <= N; i++) {
        power2[i] = (power2[i - 1] * 2) % MOD;
    }

    DSU dsu(N);
    // Track occupied holes using a set of pairs (row, col) [cite: 11]
    set<pair<int, int>> occupied;

    for (int i = 0; i < Q; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        // Check if either hole is already occupied [cite: 12, 23]
        if (occupied.count({r1, c1}) || occupied.count({r2, c2})) {
            // Discard cable, output current configuration [cite: 23]
            cout << power2[dsu.components] << "\n";
        } else {
            // Mark holes as occupied and connect columns [cite: 13]
            occupied.insert({r1, c1});
            occupied.insert({r2, c2});
            dsu.unite(c1, c2);
            cout << power2[dsu.components] << "\n";
        }
    }

    return 0;
}