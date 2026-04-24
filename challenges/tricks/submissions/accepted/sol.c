#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

// --- Treap Structure ---
typedef struct {
    ll val;
    int priority;
    int left, right;
} Node;

Node pool[1000005];
int node_count = 0;

int create_node(ll val) {
    int id = ++node_count;
    pool[id].val = val;
    pool[id].priority = rand();
    pool[id].left = pool[id].right = 0;
    return id;
}

void split(int node, ll val, int *l, int *r) {
    if (!node) {
        *l = *r = 0;
        return;
    }
    if (pool[node].val <= val) {
        *l = node;
        split(pool[node].right, val, &pool[node].right, r);
    } else {
        *r = node;
        split(pool[node].left, val, l, &pool[node].left);
    }
}

// Splits exactly one instance of val from the tree
void split_one(int node, ll val, int *l, int *m, int *r) {
    if (!node) {
        *l = *m = *r = 0;
        return;
    }
    if (pool[node].val < val) {
        *l = node;
        split_one(pool[node].right, val, &pool[node].right, m, r);
    } else if (pool[node].val > val) {
        *r = node;
        split_one(pool[node].left, val, l, m, &pool[node].left);
    } else {
        // Isolate this specific node
        *m = node;
        *l = pool[node].left;
        *r = pool[node].right;
        pool[node].left = pool[node].right = 0;
    }
}

int merge(int l, int r) {
    if (!l || !r) return l | r;
    if (pool[l].priority > pool[r].priority) {
        pool[l].right = merge(pool[l].right, r);
        return l;
    } else {
        pool[r].left = merge(l, pool[r].left);
        return r;
    }
}

// --- Logic Functions ---

ll rev(ll x) {
    unsigned int res = (unsigned int)x;
    for (int i = 0; i < 16; i++) {
        unsigned int bit_i = (res >> i) & 1;
        unsigned int bit_opp = (res >> (31 - i)) & 1;
        if (bit_i != bit_opp) {
            res ^= (1U << i);
            res ^= (1U << (31 - i));
        }
    }
    return (ll)res;
}

int main() {
    int q;
    if (scanf("%d", &q) != 1) return 0;

    int root1 = 0, root2 = 0;
    ll sum1 = 0, sum2 = 0;
    int size = 0;
    bool bl = true;

    while (q--) {
        int typ;
        scanf("%d", &typ);

        if (typ == 1) {
            ll x;
            scanf("%lld", &x);
            ll x2 = rev(x);
            int l, r;
            if (bl) {
                split(root1, x, &l, &r);
                root1 = merge(merge(l, create_node(x)), r);
                split(root2, x2, &l, &r);
                root2 = merge(merge(l, create_node(x2)), r);
                sum1 += x; sum2 += x2;
            } else {
                split(root2, x, &l, &r);
                root2 = merge(merge(l, create_node(x)), r);
                split(root1, x2, &l, &r);
                root1 = merge(merge(l, create_node(x2)), r);
                sum2 += x; sum1 += x2;
            }
            size++;
        } 
        else if (typ == 2) {
            ll mean = (bl ? sum1 : sum2) / size;
            int curr = (bl ? root1 : root2);
            ll best = -1;

            // Find floorKey(mean)
            while (curr) {
                if (pool[curr].val <= mean) {
                    best = pool[curr].val;
                    curr = pool[curr].right;
                } else {
                    curr = pool[curr].left;
                }
            }

            ll best_rev = rev(best);
            int l, m, r;

            // Remove best from root1 and best_rev from root2 (or vice versa)
            split_one(root1, (bl ? best : best_rev), &l, &m, &r);
            root1 = merge(l, r);
            
            split_one(root2, (bl ? best_rev : best), &l, &m, &r);
            root2 = merge(l, r);

            sum1 -= (bl ? best : best_rev);
            sum2 -= (bl ? best_rev : best);
            
            printf("%lld\n", best);
            size--;
        } 
        else if (typ == 3) {
            bl = !bl;
        }
    }

    return 0;
}