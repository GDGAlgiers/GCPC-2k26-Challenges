#include <bits/stdc++.h>
using namespace std;

using ll = long long;
static const ll INF = (ll)4e18;

struct Edge {
    int to;
    ll w;
};

struct Road {
    int u, v;
    ll w;
};

vector<ll> dijkstra(int src, const vector<vector<Edge>> &graph) {
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
        for (const auto &e : graph[u]) {
            ll nd = d + e.w;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                pq.push({nd, e.to});
            }
        }
    }

    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    vector<Road> roads;
    roads.reserve(m);

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        roads.push_back({u, v, w});
    }

    vector<ll> dist_start = dijkstra(1, graph);
    vector<ll> dist_end = dijkstra(n, graph);

    ll ans = dist_start[n];
    for (const auto &road : roads) {
        if (dist_start[road.u] < INF / 2 && dist_end[road.v] < INF / 2) {
            ans = min(ans, dist_start[road.u] + dist_end[road.v]);
        }
        if (dist_start[road.v] < INF / 2 && dist_end[road.u] < INF / 2) {
            ans = min(ans, dist_start[road.v] + dist_end[road.u]);
        }
    }

    cout << (ans >= INF / 2 ? -1 : ans) << '\n';
    return 0;
}
