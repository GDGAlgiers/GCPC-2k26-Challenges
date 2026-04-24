#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int to;
    int next;
    ll w;
} Edge;

typedef struct {
    int u, v;
} Road;

typedef struct {
    ll dist;
    int node;
} HeapNode;

static const ll INF = 4000000000000000000LL;

static int n, m;
static int *head;
static Edge *edges;
static int edge_count;
static Road *roads;

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

int main(void) {
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    head = (int *)malloc((n + 1) * sizeof(int));
    edges = (Edge *)malloc((2 * m + 5) * sizeof(Edge));
    roads = (Road *)malloc((m > 0 ? m : 1) * sizeof(Road));
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
        roads[i].u = u;
        roads[i].v = v;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    ll *dist_start = (ll *)malloc((n + 1) * sizeof(ll));
    ll *dist_end = (ll *)malloc((n + 1) * sizeof(ll));

    dijkstra(1, dist_start);
    dijkstra(n, dist_end);

    ll ans = dist_start[n];
    for (int i = 0; i < m; ++i) {
        int u = roads[i].u;
        int v = roads[i].v;
        if (dist_start[u] < INF / 2 && dist_end[v] < INF / 2) {
            ll cand = dist_start[u] + dist_end[v];
            if (cand < ans) {
                ans = cand;
            }
        }
        if (dist_start[v] < INF / 2 && dist_end[u] < INF / 2) {
            ll cand = dist_start[v] + dist_end[u];
            if (cand < ans) {
                ans = cand;
            }
        }
    }

    printf("%lld\n", ans >= INF / 2 ? -1LL : ans);
    return 0;
}
