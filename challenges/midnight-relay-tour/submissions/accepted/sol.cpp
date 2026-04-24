#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static const ll INF = (ll)4e18;

vector<ll> dijkstra(int src, const vector<vector<pair<int, ll>>> &graph) {
    int n = (int)graph.size() - 1;
    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) {
            continue;
        }
        for (auto [v, w] : graph[u]) {
            ll nd = d + w;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> relays(k);
    for (int i = 0; i < k; ++i) {
        cin >> relays[i];
    }

    vector<vector<pair<int, ll>>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<int> important;
    important.push_back(1);
    for (int x : relays) {
        important.push_back(x);
    }
    important.push_back(n);

    int cnt = (int)important.size();
    vector<vector<ll>> dist_imp(cnt, vector<ll>(cnt, INF));
    for (int i = 0; i < cnt; ++i) {
        vector<ll> dist = dijkstra(important[i], graph);
        for (int j = 0; j < cnt; ++j) {
            dist_imp[i][j] = dist[important[j]];
        }
    }

    if (k == 0) {
        ll ans = dist_imp[0][1];
        cout << (ans >= INF / 2 ? -1 : ans) << '\n';
        return 0;
    }

    int max_mask = 1 << k;
    vector<vector<ll>> dp(max_mask, vector<ll>(k, INF));
    for (int i = 0; i < k; ++i) {
        dp[1 << i][i] = dist_imp[0][i + 1];
    }

    for (int mask = 0; mask < max_mask; ++mask) {
        for (int i = 0; i < k; ++i) {
            ll cur = dp[mask][i];
            if (cur >= INF / 2) {
                continue;
            }
            for (int j = 0; j < k; ++j) {
                if (mask & (1 << j)) {
                    continue;
                }
                int next_mask = mask | (1 << j);
                ll nd = cur + dist_imp[i + 1][j + 1];
                if (nd < dp[next_mask][j]) {
                    dp[next_mask][j] = nd;
                }
            }
        }
    }

    ll ans = INF;
    int full = max_mask - 1;
    for (int i = 0; i < k; ++i) {
        ans = min(ans, dp[full][i] + dist_imp[i + 1][k + 1]);
    }

    cout << (ans >= INF / 2 ? -1 : ans) << '\n';
    return 0;
}
