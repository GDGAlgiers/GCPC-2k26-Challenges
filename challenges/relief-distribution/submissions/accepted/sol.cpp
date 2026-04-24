#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> boxes;
    boxes.reserve(n);

    for (int i = 0; i < n; i++) {
        int w, d;
        cin >> w >> d;
        boxes.push_back({d, w});
    }

    sort(boxes.begin(), boxes.end());

    priority_queue<int> pq;
    long long total = 0;

    for (auto [d, w] : boxes) {
        pq.push(w);
        total += w;
        if ((int)pq.size() > d) {
            total -= pq.top();
            pq.pop();
        }
    }

    cout << pq.size() << ' ' << total << '\n';
    return 0;
}
