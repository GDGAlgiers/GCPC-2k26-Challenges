#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int mat[20][20];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    int min = N;

    for (int mask = 0; mask < (1 << N); mask++) {
        int covered[20] = {0};
        int count = 0;

        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                count++;
                covered[i] = 1;

                for (int j = 0; j < N; j++) {
                    if (mat[i][j] == 1) {
                        covered[j] = 1;
                    }
                }
            }
        }

        int ok = 1;
        for (int i = 0; i < N; i++) {
            if (!covered[i]) {
                ok = 0;
                break;
            }
        }

        if (ok && count < min) {
            min = count;
        }
    }

    printf("%d\n", min);

    return 0;
}
