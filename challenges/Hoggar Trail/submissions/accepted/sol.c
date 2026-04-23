// Author: Corvus, Firas Mohamed Elamine Kiram

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(s) (int)(s).size()
#define all(s) s.begin(),s.end()

void Speed() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

const int M = 1e9 + 7, N = 1e5 + 10;
int add(int a, int b){
    return (a + b) % M;
}
int mul(int a, int b){
    return 1ll * a * b % M;
}
int sub(int a, int b){
    return ((a - b) % M + M) % M;
}
int pw[N];


struct Node {
    int cnt = 0, sum = 0;
} neutral;

struct segtree {
    segtree *left = nullptr, *right = nullptr;

    Node node = {};

    int start, end;

    segtree(int l = 0, int r = 0) : start(l), end(r) {}

    void extend() {
        if (left == nullptr) {
            int mid = start + end >> 1;
            left = new segtree(start, mid);
            right = new segtree(mid + 1, end);
        }
    }

    Node pushup(Node a, Node b) {
        Node ret;
        ret.cnt = add(a.cnt, b.cnt);
        ret.sum = add(a.sum, b.sum);
        return ret;
    }
    
    void update(int idx, int sum, int cnt) {
        if (start > idx || end < idx)
            return;
        if (start == end) {
            node.cnt = add(node.cnt, cnt);
            node.sum = add(node.sum, sum);
            return;
        }
        extend();
        left->update(idx, sum, cnt);
        right->update(idx, sum, cnt);
        node = pushup(left->node, right->node);
    }

    Node query(int l, int r) {
        if (r < start || end < l)
            return neutral;
        extend();
        if (l <= start && end <= r)
            return node;
        Node ret = pushup(left->query(l , r), right->query(l , r));
        return ret;
    }

    ~segtree() {
        if (left == nullptr)return;
        delete left;
        delete right;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    map<int, int> mp;
    for(auto& it : a) cin >> it, mp[it] = 1;
    int nxt = 1;
    for(auto& [k, v] : mp) v = nxt++;

    segtree* root = new segtree(0, nxt + 5);
    int ans = 0;
    for(int i = 0; i < n; i++){
        int x = a[i];
        a[i] = mp[a[i]];
        auto left = root->query(0, a[i] - 1), right = root->query(a[i] + 1, nxt + 5);
        int cur = sub(mul(left.cnt, x), left.sum);
        cur = add(cur, sub(right.sum, mul(right.cnt, x)));
        ans = add(ans, mul(cur, pw[n - i - 1]));
        root->update(a[i], mul(x, pw[i]), pw[i]);
    }
    cout << ans << '\n';
}

int main() {
    pw[0] = 1;
    for(int i = 1; i < N; i++){
        pw[i] = pw[i - 1] << 1;
        pw[i] %= M;
    }
    Speed();
    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}