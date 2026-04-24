#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int mat[20][20];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> mat[i][j];
        }
    }

    int best = N;

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

        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (!covered[i]) {
                ok = false;
                break;
            }
        }

        if (ok && count < best) {
            best = count;
        }
    }

    cout << best << '\n';
    return 0;
}
