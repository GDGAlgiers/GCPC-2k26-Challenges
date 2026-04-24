// Accepted solution — C++17
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, B;
    cin >> N >> B;

    vector<long long> dp(B + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < N; i++) {
        int k;
        cin >> k;
        vector<int> replicas(k);
        for (int j = 0; j < k; j++) cin >> replicas[j];

        vector<long long> ndp(B + 1, 0);
        for (int latency : replicas)
            for (int b = latency; b <= B; b++)
                ndp[b] += dp[b - latency];
        dp = ndp;
    }

    cout << accumulate(dp.begin(), dp.end(), 0LL) << "\n";
    return 0;
}
