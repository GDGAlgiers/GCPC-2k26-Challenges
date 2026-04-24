// Author: Corvus, Firas Mohamed Elamine Kiram

#include "bits/stdc++.h"
using namespace std;
using ll = long long;
#define endl '\n'
#define int ll


int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

const int N = 2005, oo = 2e18, mod = 998244353;
int in[N][N], dist[N][N], add[N][N], window[N];

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b&1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod, b >>= 1;
    }
    return res;
}

int valid(int x, int y) {
    if(min(x, y) < 0) return 0;
    return in[x][y];
}

void bfs(vector<array<int, 2>> &sources) {
    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j) dist[i][j] = oo;

    queue<array<int, 2>> q;
    for(auto &[x, y]: sources) {
        dist[x][y] = 0;
        q.push({x, y});
    }

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int k = 0; k < 4; ++k) {
            int nx = x + dx[k], ny = y + dy[k];
            if(dist[nx][ny] < oo || !valid(nx, ny)) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
}

void magic() {
    int n; cin >> n;
    vector<array<int, 2>> p(n);
    for(auto &[x, y]: p) cin >> x >> y;
    p.push_back(p[0]);

    for(int i = 1; i <= n; ++i) {
        auto &[x, y] = p[i];
        auto &[px, py] = p[i - 1];
        for(int j = min(py, y); j <= max(py, y); ++j) in[x][j] = 1;
        for(int j = min(px, x); j <= max(px, x); ++j) in[j][y] = 1;
        for(int j = min(py, y); j < max(py, y); ++j)  add[x][j] = 1;
    }

    vector<array<int, 2>> sources;
    for(int x = 0; x < N; ++x) {
        for(int y = 0; y < N; ++y) {
            if(in[x][y]) sources.push_back({x, y});
            in[x][y] |= window[y] & 1;
            window[y] += add[x][y];
        }
    }

    bfs(sources);
    vector<int> vals;
    for(int x = 0; x < N; ++x)
        for(int y = 0; y < N; ++y)
            if(in[x][y]) vals.push_back(dist[x][y]);

    sort(vals.begin(), vals.end());

    int ans = 0, pw = 1;
    for(int i = 0; i < size(vals); ++i, pw = pw * 2 % mod) {
        ans += vals[i] * pw % mod;
        ans %= mod;
    }

    cout << ans * power(pw - 1, mod - 2) % mod << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}