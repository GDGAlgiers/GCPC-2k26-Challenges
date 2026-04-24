#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll c;
    int neg;
} Node;

static int better(Node a, Node b) {
    if (a.c != b.c) return a.c > b.c;
    return a.neg > b.neg;
}

static void heap_push(Node *h, int *sz, Node v) {
    int i = ++(*sz);
    h[i] = v;
    while (i > 1) {
        int p = i >> 1;
        if (!better(h[i], h[p])) break;
        Node t = h[i]; h[i] = h[p]; h[p] = t;
        i = p;
    }
}

static Node heap_pop(Node *h, int *sz) {
    Node ret = h[1];
    h[1] = h[(*sz)--];
    int i = 1;
    while (1) {
        int l = i << 1;
        int r = l + 1;
        int m = i;
        if (l <= *sz && better(h[l], h[m])) m = l;
        if (r <= *sz && better(h[r], h[m])) m = r;
        if (m == i) break;
        Node t = h[i]; h[i] = h[m]; h[m] = t;
        i = m;
    }
    return ret;
}

int main(void) {
    int k, q;
    if (scanf("%d %d", &k, &q) != 2) return 0;

    ll *cnt = (ll *)calloc((size_t)(k + 1), sizeof(ll));
    int cap = k + 4 * q + 10;
    Node *heap = (Node *)malloc((size_t)cap * sizeof(Node));
    if (!cnt || !heap) {
        free(cnt);
        free(heap);
        return 0;
    }

    int sz = 0;
    for (int i = 1; i <= k; i++) heap_push(heap, &sz, (Node){0, -i});

    char op[16];
    while (q--) {
        scanf("%15s", op);

        if (strcmp(op, "ADD") == 0) {
            int g;
            ll x;
            scanf("%d %lld", &g, &x);
            cnt[g] += x;
            heap_push(heap, &sz, (Node){cnt[g], -g});
        } else if (strcmp(op, "SERVE") == 0) {
            int g;
            ll x;
            scanf("%d %lld", &g, &x);
            ll t = cnt[g] < x ? cnt[g] : x;
            cnt[g] -= t;
            heap_push(heap, &sz, (Node){cnt[g], -g});
        } else if (strcmp(op, "MOVE") == 0) {
            int a, b;
            ll x;
            scanf("%d %d %lld", &a, &b, &x);
            ll t = cnt[a] < x ? cnt[a] : x;
            cnt[a] -= t;
            cnt[b] += t;
            heap_push(heap, &sz, (Node){cnt[a], -a});
            heap_push(heap, &sz, (Node){cnt[b], -b});
        } else if (strcmp(op, "MERGE") == 0) {
            int a, b;
            scanf("%d %d", &a, &b);
            cnt[a] += cnt[b];
            cnt[b] = 0;
            heap_push(heap, &sz, (Node){cnt[a], -a});
            heap_push(heap, &sz, (Node){cnt[b], -b});
        } else {
            while (1) {
                Node top = heap[1];
                int idx = -top.neg;
                if (top.c == cnt[idx]) {
                    printf("%d %lld\n", idx, top.c);
                    break;
                }
                heap_pop(heap, &sz);
            }
        }
    }

    free(cnt);
    free(heap);
    return 0;
}
