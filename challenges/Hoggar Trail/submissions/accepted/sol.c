#include <stdio.h>
#include <stdlib.h>

#define M 1000000007
#define N 100010

typedef long long ll;

int add(int a, int b) {
    return (a + b) % M;
}

int mul(int a, int b) {
    return (int)((1LL * a * b) % M);
}

int sub(int a, int b) {
    return ((a - b) % M + M) % M;
}

int pw[N];

typedef struct Node {
    int cnt;
    int sum;
} Node;

Node neutral = {0, 0};

typedef struct segtree {
    struct segtree *left, *right;
    Node node;
    int start, end;
} segtree;

segtree* create_segtree(int l, int r) {
    segtree* st = (segtree*)malloc(sizeof(segtree));
    st->left = NULL;
    st->right = NULL;
    st->node.cnt = 0;
    st->node.sum = 0;
    st->start = l;
    st->end = r;
    return st;
}

void extend(segtree* st) {
    if (st->left == NULL) {
        int mid = st->start + (st->end - st->start) / 2;
        st->left = create_segtree(st->start, mid);
        st->right = create_segtree(mid + 1, st->end);
    }
}

Node pushup(Node a, Node b) {
    Node ret;
    ret.cnt = add(a.cnt, b.cnt);
    ret.sum = add(a.sum, b.sum);
    return ret;
}

void update(segtree* st, int idx, int sum, int cnt) {
    if (st->start > idx || st->end < idx)
        return;
    if (st->start == st->end) {
        st->node.cnt = add(st->node.cnt, cnt);
        st->node.sum = add(st->node.sum, sum);
        return;
    }
    extend(st);
    update(st->left, idx, sum, cnt);
    update(st->right, idx, sum, cnt);
    st->node = pushup(st->left->node, st->right->node);
}

Node query(segtree* st, int l, int r) {
    if (r < st->start || st->end < l)
        return neutral;
    extend(st);
    if (l <= st->start && st->end <= r)
        return st->node;
    Node ret = pushup(query(st->left, l, r), query(st->right, l, r));
    return ret;
}

void free_segtree(segtree* st) {
    if (st == NULL) return;
    free_segtree(st->left);
    free_segtree(st->right);
    free(st);
}

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void solve() {
    int n;
    if (scanf("%d", &n) != 1) return;
    
    int *a = (int*)malloc(n * sizeof(int));
    int *sorted_a = (int*)malloc(n * sizeof(int));
    
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sorted_a[i] = a[i];
    }

    // Coordinate Compression (equivalent to map)
    qsort(sorted_a, n, sizeof(int), cmp);
    int unique_count = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || sorted_a[i] != sorted_a[i - 1]) {
            sorted_a[unique_count++] = sorted_a[i];
        }
    }

    int nxt = unique_count + 1;
    segtree* root = create_segtree(0, nxt + 5);
    int ans = 0;
    
    for(int i = 0; i < n; i++){
        int x = a[i];
        
        // Binary search to find rank (1-based index)
        int low = 0, high = unique_count - 1;
        int rank = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (sorted_a[mid] == x) {
                rank = mid + 1;
                break;
            } else if (sorted_a[mid] < x) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        a[i] = rank;
        
        Node left_res = query(root, 0, a[i] - 1);
        Node right_res = query(root, a[i] + 1, nxt + 5);
        int cur = sub(mul(left_res.cnt, x), left_res.sum);
        cur = add(cur, sub(right_res.sum, mul(right_res.cnt, x)));
        ans = add(ans, mul(cur, pw[n - i - 1]));
        update(root, a[i], mul(x, pw[i]), pw[i]);
    }
    printf("%d\n", ans);

    free_segtree(root);
    free(a);
    free(sorted_a);
}

int main() {
    pw[0] = 1;
    for(int i = 1; i < N; i++){
        pw[i] = (pw[i - 1] << 1) % M;
    }
    int tc = 1;
    // scanf("%d", &tc);
    while (tc--) {
        solve();
    }
    return 0;
}