// Accepted solution — C++17
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, W, X, C;
    cin >> N >> W >> X >> C;

    int E;
    cin >> E;

    vector<vector<int>> failures(N);

    for (int i = 0; i < E; i++) {
        int T, S, R;
        cin >> T >> S >> R;
        if (R == 0) failures[S].push_back(T);
    }

    using Interval = pair<int,int>;
    vector<vector<Interval>> intervals(N);

    for (int s = 0; s < N; s++) {
        auto &fl = failures[s];
        int skipUntil = -1;
        deque<int> valid;

        for (int t : fl) {
            if (t < skipUntil) continue;
            valid.push_back(t);
            while (!valid.empty() && valid.front() < t - W)
                valid.pop_front();
            if ((int)valid.size() == X) {
                int openTime  = t;
                int closeTime = openTime + C;
                intervals[s].push_back({openTime, closeTime});
                skipUntil = closeTime;
                valid.clear();
            }
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int T, S;
        cin >> T >> S;
        auto &ivs = intervals[S];
        int lo = 0, hi = (int)ivs.size() - 1;
        bool found = false;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (ivs[mid].first <= T) {
                if (ivs[mid].second > T) { found = true; break; }
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        cout << (found ? "OPEN" : "CLOSED") << "\n";
    }

    return 0;
}
