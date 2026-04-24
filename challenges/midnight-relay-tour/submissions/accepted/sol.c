#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    int to;
    int next;
    ll w;
} Edge;

typedef struct {
    ll dist;
    int node;
} HeapNode;

static const ll INF = 4000000000000000000LL;

static int n, m, k;
static int *head;
static Edge *edges;
static int edge_count;

static HeapNode *heap_arr;
static int heap_size;

static void add_edge(int u, int v, ll w) {
    edges[edge_count].to = v;
    edges[edge_count].w = w;
    edges[edge_count].next = head[u];
    head[u] = edge_count++;
}

static void heap_push(ll dist, int node) {
    int idx = ++heap_size;
    heap_arr[idx].dist = dist;
    heap_arr[idx].node = node;
    while (idx > 1) {
        int parent = idx / 2;
        if (heap_arr[parent].dist <= heap_arr[idx].dist) {
            break;
        }
        HeapNode tmp = heap_arr[parent];
        heap_arr[parent] = heap_arr[idx];
        heap_arr[idx] = tmp;
        idx = parent;
    }
}

static HeapNode heap_pop(void) {
    HeapNode ret = heap_arr[1];
    heap_arr[1] = heap_arr[heap_size--];

    int idx = 1;
    while (1) {
        int left = idx * 2;
        int right = left + 1;
        int smallest = idx;

        if (left <= heap_size && heap_arr[left].dist < heap_arr[smallest].dist) {
            smallest = left;
        }
        if (right <= heap_size && heap_arr[right].dist < heap_arr[smallest].dist) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        HeapNode tmp = heap_arr[idx];
        heap_arr[idx] = heap_arr[smallest];
        heap_arr[smallest] = tmp;
        idx = smallest;
    }

    return ret;
}

static void dijkstra(int src, ll *dist) {
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }

    dist[src] = 0;
    heap_size = 0;
    heap_push(0, src);

    while (heap_size > 0) {
        HeapNode cur = heap_pop();
        if (cur.dist != dist[cur.node]) {
            continue;
        }

        for (int e = head[cur.node]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            ll nd = cur.dist + edges[e].w;
            if (nd < dist[v]) {
                dist[v] = nd;
                heap_push(nd, v);
            }
        }
    }
}

static ll min_ll(ll a, ll b) {
    return a < b ? a : b;
}

int main(void) {
    if (scanf("%d %d %d", &n, &m, &k) != 3) {
        return 0;
    }

    int *relays = (int *)malloc((k > 0 ? k : 1) * sizeof(int));
    for (int i = 0; i < k; ++i) {
        if (scanf("%d", &relays[i]) != 1) {
            return 0;
        }
    }

    head = (int *)malloc((n + 1) * sizeof(int));
    edges = (Edge *)malloc((2 * m + 5) * sizeof(Edge));
    heap_arr = (HeapNode *)malloc((2 * m + 5) * sizeof(HeapNode));

    for (int i = 0; i <= n; ++i) {
        head[i] = -1;
    }
    edge_count = 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        if (scanf("%d %d %lld", &u, &v, &w) != 3) {
            return 0;
        }
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int important_count = k + 2;
    int *important = (int *)malloc(important_count * sizeof(int));
    important[0] = 1;
    for (int i = 0; i < k; ++i) {
        important[i + 1] = relays[i];
    }
    important[k + 1] = n;

    ll **dist_imp = (ll **)malloc(important_count * sizeof(ll *));
    for (int i = 0; i < important_count; ++i) {
        dist_imp[i] = (ll *)malloc(important_count * sizeof(ll));
    }

    ll *dist = (ll *)malloc((n + 1) * sizeof(ll));
    for (int i = 0; i < important_count; ++i) {
        dijkstra(important[i], dist);
        for (int j = 0; j < important_count; ++j) {
            dist_imp[i][j] = dist[important[j]];
        }
    }

    if (k == 0) {
        ll ans = dist_imp[0][1];
        printf("%lld\n", ans >= INF / 2 ? -1LL : ans);
        return 0;
    }

    int max_mask = 1 << k;
    ll *dp = (ll *)malloc((size_t)max_mask * (size_t)k * sizeof(ll));
    for (int mask = 0; mask < max_mask; ++mask) {
        for (int i = 0; i < k; ++i) {
            dp[mask * k + i] = INF;
        }
    }

    for (int i = 0; i < k; ++i) {
        dp[(1 << i) * k + i] = dist_imp[0][i + 1];
    }

    for (int mask = 0; mask < max_mask; ++mask) {
        for (int i = 0; i < k; ++i) {
            ll cur = dp[mask * k + i];
            if (cur >= INF / 2) {
                continue;
            }
            for (int j = 0; j < k; ++j) {
                if (mask & (1 << j)) {
                    continue;
                }
                int next_mask = mask | (1 << j);
                ll nd = cur + dist_imp[i + 1][j + 1];
                if (nd < dp[next_mask * k + j]) {
                    dp[next_mask * k + j] = nd;
                }
            }
        }
    }

    ll ans = INF;
    int full = max_mask - 1;
    for (int i = 0; i < k; ++i) {
        ans = min_ll(ans, dp[full * k + i] + dist_imp[i + 1][k + 1]);
    }

    printf("%lld\n", ans >= INF / 2 ? -1LL : ans);
    return 0;
}
