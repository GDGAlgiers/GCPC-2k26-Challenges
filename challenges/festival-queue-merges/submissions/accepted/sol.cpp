#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, q;
    if (!(cin >> k >> q)) return 0;

    vector<long long> cnt(k + 1, 0);
    priority_queue<pair<long long, int>> pq;

    for (int i = 1; i <= k; i++) pq.push({0, -i});

    while (q--) {
        string op;
        cin >> op;

        if (op == "ADD") {
            int g;
            long long x;
            cin >> g >> x;
            cnt[g] += x;
            pq.push({cnt[g], -g});
        } else if (op == "SERVE") {
            int g;
            long long x;
            cin >> g >> x;
            long long t = min(cnt[g], x);
            cnt[g] -= t;
            pq.push({cnt[g], -g});
        } else if (op == "MOVE") {
            int a, b;
            long long x;
            cin >> a >> b >> x;
            long long t = min(cnt[a], x);
            cnt[a] -= t;
            cnt[b] += t;
            pq.push({cnt[a], -a});
            pq.push({cnt[b], -b});
        } else if (op == "MERGE") {
            int a, b;
            cin >> a >> b;
            cnt[a] += cnt[b];
            cnt[b] = 0;
            pq.push({cnt[a], -a});
            pq.push({cnt[b], -b});
        } else {
            while (true) {
                auto top = pq.top();
                int idx = -top.second;
                if (top.first == cnt[idx]) {
                    cout << idx << ' ' << top.first << '\n';
                    break;
                }
                pq.pop();
            }
        }
    }

    return 0;
}
