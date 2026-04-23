// Author: Corvus, Firas Mohamed Elamine Kiram
// Translated to C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N    2005
#define MOD  998244353LL
#define QMAX (N * N * 2)
#define PMAX 100005

typedef long long ll;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

ll in_grid  [N][N];
ll dist_grid[N][N];
ll add_grid [N][N];
ll window_arr[N];

ll power_mod(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int valid(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y >= N) return 0;
    return in_grid[x][y] != 0;
}

typedef struct { int x, y; } Point;

Point bfs_queue[QMAX];

void bfs(Point *sources, int src_count) {
    /* -1 = unvisited */
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dist_grid[i][j] = -1;

    int head = 0, tail = 0;
    for (int i = 0; i < src_count; i++) {
        int x = sources[i].x, y = sources[i].y;
        if (dist_grid[x][y] != -1) continue;
        dist_grid[x][y] = 0;
        bfs_queue[tail++] = sources[i];
    }

    while (head < tail) {
        Point cur = bfs_queue[head++];
        int x = cur.x, y = cur.y;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (!valid(nx, ny))          continue;
            if (dist_grid[nx][ny] != -1) continue;
            dist_grid[nx][ny] = dist_grid[x][y] + 1;
            bfs_queue[tail++] = (Point){nx, ny};
        }
    }
}

int cmp_ll(const void *a, const void *b) {
    ll x = *(ll *)a, y = *(ll *)b;
    return (x > y) - (x < y);
}

int      px[PMAX], py[PMAX];
Point    sources[N * N];
ll       vals   [N * N];

void magic() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) scanf("%d %d", &px[i], &py[i]);
    px[n] = px[0];
    py[n] = py[0];

    memset(in_grid,    0, sizeof(in_grid));
    memset(add_grid,   0, sizeof(add_grid));
    memset(window_arr, 0, sizeof(window_arr));

    for (int i = 1; i <= n; i++) {
        int x = px[i],   y   = py[i];
        int ppx = px[i-1], ppy = py[i-1];

        int ylo = ppy < y ? ppy : y;
        int yhi = ppy > y ? ppy : y;
        for (int j = ylo; j <= yhi; j++) in_grid[x][j] = 1;

        int xlo = ppx < x ? ppx : x;
        int xhi = ppx > x ? ppx : x;
        for (int j = xlo; j <= xhi; j++) in_grid[j][y] = 1;

        for (int j = ylo; j < yhi; j++) add_grid[x][j] = 1;
    }

    int src_count = 0;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (in_grid[x][y]) sources[src_count++] = (Point){x, y};
            in_grid[x][y] |= (window_arr[y] & 1);
            window_arr[y] += add_grid[x][y];
        }
    }

    bfs(sources, src_count);

    int vcount = 0;
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            if (in_grid[x][y]) vals[vcount++] = dist_grid[x][y];

    qsort(vals, vcount, sizeof(ll), cmp_ll);

    ll ans = 0, pw = 1;
    for (int i = 0; i < vcount; i++) {
        ans = (ans + vals[i] % MOD * pw) % MOD;
        pw  = pw * 2 % MOD;
    }

    printf("%lld\n", ans * power_mod(pw - 1, MOD - 2) % MOD);
}

int main() {
    magic();
    return 0;
}