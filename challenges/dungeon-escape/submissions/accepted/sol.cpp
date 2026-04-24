#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<string> grid(n);
    int sr = -1, sc = -1, er = -1, ec = -1;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'S') {
                sr = i; sc = j;
            } else if (grid[i][j] == 'E') {
                er = i; ec = j;
            }
        }
    }
    
    if (sr == -1 || er == -1) {
        cout << -1 << "\n";
        return 0;
    }
    
    vector<vector<vector<bool>>> vis(n, vector<vector<bool>>(m, vector<bool>(2, false)));
    queue<tuple<int, int, int, int>> q;
    
    q.push({sr, sc, 0, 0});
    vis[sr][sc][0] = true;
    
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
        auto [r, c, has_key, steps] = q.front();
        q.pop();
        
        if (r == er && c == ec) {
            cout << steps << "\n";
            return 0;
        }
        
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                char cell = grid[nr][nc];
                if (cell == '#') continue;
                
                int n_key = has_key;
                if (cell == 'k') n_key = 1;
                else if (cell == 'K' && has_key == 0) continue;
                
                if (!vis[nr][nc][n_key]) {
                    vis[nr][nc][n_key] = true;
                    q.push({nr, nc, n_key, steps + 1});
                }
            }
        }
    }
    
    cout << -1 << "\n";
    return 0;
}
