#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int r, c, has_key, steps;
} Node;

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    
    char **grid = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        grid[i] = (char *)malloc((m + 1) * sizeof(char));
        scanf("%s", grid[i]);
    }
    
    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sr = i; sc = j;
            } else if (grid[i][j] == 'E') {
                er = i; ec = j;
            }
        }
    }
    
    if (sr == -1 || er == -1) {
        printf("-1\n");
        return 0;
    }
    
    // vis[r][c][has_key]
    int ***vis = (int ***)malloc(n * sizeof(int **));
    for (int i = 0; i < n; i++) {
        vis[i] = (int **)malloc(m * sizeof(int *));
        for (int j = 0; j < m; j++) {
            vis[i][j] = (int *)calloc(2, sizeof(int));
        }
    }
    
    Node *q = (Node *)malloc(n * m * 2 * sizeof(Node));
    int head = 0, tail = 0;
    
    q[tail++] = (Node){sr, sc, 0, 0};
    vis[sr][sc][0] = 1;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while (head < tail) {
        Node curr = q[head++];
        
        if (curr.r == er && curr.c == ec) {
            printf("%d\n", curr.steps);
            return 0;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                char cell = grid[nr][nc];
                if (cell == '#') continue;
                
                int n_key = curr.has_key;
                if (cell == 'k') n_key = 1;
                else if (cell == 'K' && curr.has_key == 0) continue;
                
                if (!vis[nr][nc][n_key]) {
                    vis[nr][nc][n_key] = 1;
                    q[tail++] = (Node){nr, nc, n_key, curr.steps + 1};
                }
            }
        }
    }
    
    printf("-1\n");
    return 0;
}
