#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int d;
    int w;
} Box;

static int cmp_box(const void *a, const void *b) {
    const Box *x = (const Box *)a;
    const Box *y = (const Box *)b;
    if (x->d != y->d) return x->d - y->d;
    return x->w - y->w;
}

static void heap_push(int *heap, int *sz, int v) {
    int i = ++(*sz);
    heap[i] = v;
    while (i > 1) {
        int p = i >> 1;
        if (heap[p] >= heap[i]) break;
        int t = heap[p]; heap[p] = heap[i]; heap[i] = t;
        i = p;
    }
}

static int heap_pop_max(int *heap, int *sz) {
    int ret = heap[1];
    heap[1] = heap[(*sz)--];
    int i = 1;
    while (1) {
        int l = i << 1;
        int r = l + 1;
        int m = i;
        if (l <= *sz && heap[l] > heap[m]) m = l;
        if (r <= *sz && heap[r] > heap[m]) m = r;
        if (m == i) break;
        int t = heap[i]; heap[i] = heap[m]; heap[m] = t;
        i = m;
    }
    return ret;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Box *boxes = (Box *)malloc((size_t)n * sizeof(Box));
    int *heap = (int *)malloc((size_t)(n + 5) * sizeof(int));
    if (!boxes || !heap) {
        free(boxes);
        free(heap);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        int w, d;
        scanf("%d %d", &w, &d);
        boxes[i].w = w;
        boxes[i].d = d;
    }

    qsort(boxes, (size_t)n, sizeof(Box), cmp_box);

    int sz = 0;
    long long total = 0;

    for (int i = 0; i < n; i++) {
        heap_push(heap, &sz, boxes[i].w);
        total += boxes[i].w;
        if (sz > boxes[i].d) {
            total -= heap_pop_max(heap, &sz);
        }
    }

    printf("%d %lld\n", sz, total);

    free(boxes);
    free(heap);
    return 0;
}
