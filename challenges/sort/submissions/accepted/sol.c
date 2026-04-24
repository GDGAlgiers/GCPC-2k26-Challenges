#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, k;
    scanf("%d %d", &n, &k);

    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int *vec = (int *)malloc(n * sizeof(int));
    int vecSize = 0;
    int ans = 0;

    vec[vecSize++] = 1;
    for (int i = 1; i < n; i++){
        if (a[i] * 2 > a[i - 1]){
            vec[vecSize - 1]++;
        } else {
            vec[vecSize++] = 1;
        }
    }

    for (int i = 0; i < vecSize; i++){
        int diff = vec[i] - k;
        ans += diff > 0 ? diff : 0;
    }

    printf("%d\n", ans);

    free(a);
    free(vec);
    return 0;
}
