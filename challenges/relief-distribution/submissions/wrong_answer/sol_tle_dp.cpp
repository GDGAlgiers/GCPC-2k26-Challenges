// Intentionally too slow for N = 1e5 (O(N^2) in worst case).
// This solution is logically correct but will exceed the time limit.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<pair<int, int>> boxes(n); // (deadline, weight)
    for (int i = 0; i < n; ++i) {
        int w, d;
        cin >> w >> d;
        boxes[i] = {d, w};
    }

    sort(boxes.begin(), boxes.end());

    const long long INF = (1LL << 60);
    vector<long long> dp(n + 1, INF);
    dp[0] = 0;

    // DP: dp[j] = minimum total weight to schedule exactly j boxes so far.
    // Transition for each box in descending j to avoid reuse.
    for (auto [d, w] : boxes) {
        // j <= d must hold to remain feasible by current deadline.
        for (int j = min(d, n); j >= 1; --j) {
            if (dp[j - 1] == INF) continue;
            dp[j] = min(dp[j], dp[j - 1] + w);
        }
    }

    int bestCount = 0;
    for (int j = n; j >= 0; --j) {
        if (dp[j] != INF) {
            bestCount = j;
            break;
        }
    }

    cout << bestCount << ' ' << dp[bestCount] << '\n';
    return 0;
}
