#include <stdio.h>
#include <stdlib.h>


int main() {
    int n, d;
    if (scanf("%d %d", &n, &d) != 2) return 0;
    
    long long **dp = (long long **)malloc((1 << n) * sizeof(long long *));
    for (int i = 0; i < (1 << n); ++i) {
        dp[i] = (long long *)calloc(n, sizeof(long long));
    }
    
    for (int i = 0; i < n; ++i) dp[1 << i][i] = 1;
    
    int *adj_mask = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        int limit1 = (i - d > 0) ? (i - d) : 0;
        for (int j = limit1; j < i; ++j) {
            adj_mask[i] |= (1 << j);
        }
        int limit2 = (i + d < n - 1) ? (i + d) : (n - 1);
        for (int j = limit2; j > i; --j) {
            adj_mask[i] |= (1 << j);
        }
    }
    
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i)) || dp[mask][i] == 0) continue;
            int cur = adj_mask[i] & (~mask);
            while (cur > 0) {
                int idx = __builtin_ctz(cur);
                int next_mask = mask | (1 << idx);
                dp[next_mask][idx] = (dp[next_mask][idx] + dp[mask][i]);
                cur ^= (1 << idx);
            }
        }
    }
    
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + dp[(1 << n) - 1][i]);
    }
    printf("%lld\n", ans);
    
    for (int i = 0; i < (1 << n); ++i) free(dp[i]);
    free(dp);
    free(adj_mask);
    
    return 0;
}