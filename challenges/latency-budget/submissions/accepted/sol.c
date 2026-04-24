/* Accepted solution — C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int N, B;
    scanf("%d %d", &N, &B);

    long long *dp  = calloc(B + 1, sizeof(long long));
    long long *ndp = calloc(B + 1, sizeof(long long));
    dp[0] = 1;

    for (int i = 0; i < N; i++) {
        int k;
        scanf("%d", &k);
        int *replicas = malloc(k * sizeof(int));
        for (int j = 0; j < k; j++) scanf("%d", &replicas[j]);

        memset(ndp, 0, (B + 1) * sizeof(long long));
        for (int j = 0; j < k; j++) {
            int latency = replicas[j];
            for (int b = latency; b <= B; b++)
                ndp[b] += dp[b - latency];
        }

        long long *tmp = dp; dp = ndp; ndp = tmp;
        free(replicas);
    }

    long long ans = 0;
    for (int b = 0; b <= B; b++) ans += dp[b];
    printf("%lld\n", ans);

    free(dp);
    free(ndp);
    return 0;
}
