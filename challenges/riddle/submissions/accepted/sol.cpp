#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Algerian ios::sync_with_stdio(false);
#define OI cin.tie(nullptr);

int main(){
    Algerian OI
    int n,d; cin >> n >> d;
    vector<vector<ll>> dp((1ll<<n),vector<ll>(n,0));
    for(int i = 0; i < n; ++i) dp[1ll<<i][i] = 1;
    vector<int> adj_mask(n,0);
    for (int i = 0; i < n; ++i){
        for (int j = max(i-d,0); j<i; ++j){
            adj_mask[i] |= (1ll<<j);
        }
        for (int j = min(i+d,n-1); j>i; --j){
            adj_mask[i] |= (1ll<<j);
        }
    }

    for (int mask = 1; mask < (1ll<<n); ++mask){
        for (int i = 0; i < n; ++i){
            if (!(mask & (1 << i)) || dp[mask][i] == 0) continue;
            int cur = adj_mask[i] & (~mask);
            while(cur > 0){
                int idx = __builtin_ctz(cur);
                dp[mask | (1ll<<idx)][idx] += dp[mask][i];
                cur ^= (1ll << idx);
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i){
        ans += dp[(1ll<<n)-1][i];
    }
    cout << ans;
}