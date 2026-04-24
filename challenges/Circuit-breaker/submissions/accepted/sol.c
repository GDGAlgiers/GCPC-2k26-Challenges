/* Accepted solution — C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int open, close; } Interval;

int main(void)
{
    int N, W, X, C;
    scanf("%d %d %d %d", &N, &W, &X, &C);

    int E;
    scanf("%d", &E);

    int **failures = (int **)calloc(N, sizeof(int *));
    int *fsize     = (int *)calloc(N, sizeof(int));
    int *fcap      = (int *)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        fcap[i]      = 8;
        failures[i]  = (int *)malloc(fcap[i] * sizeof(int));
    }

    for (int i = 0; i < E; i++) {
        int T, S, R;
        scanf("%d %d %d", &T, &S, &R);
        if (R == 0) {
            if (fsize[S] == fcap[S]) {
                fcap[S] *= 2;
                failures[S] = (int *)realloc(failures[S], fcap[S] * sizeof(int));
            }
            failures[S][fsize[S]++] = T;
        }
    }

    Interval **intervals = (Interval **)calloc(N, sizeof(Interval *));
    int *isize = (int *)calloc(N, sizeof(int));
    int *icap  = (int *)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        icap[i]      = 8;
        intervals[i] = (Interval *)malloc(icap[i] * sizeof(Interval));
    }

    int *valid = (int *)malloc(10000 * sizeof(int));

    for (int s = 0; s < N; s++) {
        int skipUntil = -1;
        int vstart = 0, vend = 0;

        for (int i = 0; i < fsize[s]; i++) {
            int t = failures[s][i];
            if (t < skipUntil) continue;
            valid[vend++] = t;
            while (vstart < vend && valid[vstart] < t - W)
                vstart++;
            if (vend - vstart == X) {
                int openTime  = t;
                int closeTime = openTime + C;
                if (isize[s] == icap[s]) {
                    icap[s] *= 2;
                    intervals[s] = (Interval *)realloc(intervals[s], icap[s] * sizeof(Interval));
                }
                intervals[s][isize[s]].open  = openTime;
                intervals[s][isize[s]].close = closeTime;
                isize[s]++;
                skipUntil = closeTime;
                vstart = vend = 0;
            }
        }
    }

    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int T, S;
        scanf("%d %d", &T, &S);
        Interval *ivs = intervals[S];
        int lo = 0, hi = isize[S] - 1;
        int found = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (ivs[mid].open <= T) {
                if (ivs[mid].close > T) { found = 1; break; }
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        puts(found ? "OPEN" : "CLOSED");
    }

    free(valid);
    return 0;
}
