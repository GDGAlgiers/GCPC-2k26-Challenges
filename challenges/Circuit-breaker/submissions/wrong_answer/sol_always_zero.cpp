// Wrong Answer — C++
// Expected verdict: Wrong Answer (WA)
//
// Purpose: verify the judge correctly rejects an incorrect solution.
// Bug: counts ALL failures for a service regardless of the time window or
// cooldown. Opens the circuit the moment total failures >= X and never closes.
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, W, X, C;
    cin >> N >> W >> X >> C;

    int E;
    cin >> E;

    vector<int> fail_count(N, 0);
    vector<bool> tripped(N, false);

    for (int i = 0; i < E; i++)
    {
        int T, S, R;
        cin >> T >> S >> R;
        if (R == 0) fail_count[S]++;
        if (fail_count[S] >= X) tripped[S] = true;
    }

    int Q;
    cin >> Q;
    while (Q--)
    {
        int T, S;
        cin >> T >> S;
        cout << (tripped[S] ? "OPEN" : "CLOSED") << "\n";
    }
    return 0;
}
