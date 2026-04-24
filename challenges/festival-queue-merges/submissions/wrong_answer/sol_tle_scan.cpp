// Intentionally too slow: O(K) scan on every QUERY.
// Expected verdict on strong tests: Time Limit Exceeded.
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, q;
    if (!(cin >> k >> q)) return 0;

    vector<long long> cnt(k + 1, 0);

    while (q--) {
        string op;
        cin >> op;

        if (op == "ADD") {
            int g;
            long long x;
            cin >> g >> x;
            cnt[g] += x;
        } else if (op == "SERVE") {
            int g;
            long long x;
            cin >> g >> x;
            cnt[g] -= min(cnt[g], x);
        } else if (op == "MOVE") {
            int a, b;
            long long x;
            cin >> a >> b >> x;
            long long t = min(cnt[a], x);
            cnt[a] -= t;
            cnt[b] += t;
        } else if (op == "MERGE") {
            int a, b;
            cin >> a >> b;
            cnt[a] += cnt[b];
            cnt[b] = 0;
        } else {
            int bestIdx = 1;
            long long bestVal = cnt[1];
            for (int i = 2; i <= k; i++) {
                if (cnt[i] > bestVal) {
                    bestVal = cnt[i];
                    bestIdx = i;
                }
            }
            cout << bestIdx << ' ' << bestVal << '\n';
        }
    }

    return 0;
}
