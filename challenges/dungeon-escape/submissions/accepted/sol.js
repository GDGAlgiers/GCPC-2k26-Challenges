const fs = require('fs');

function solve() {
    const input = fs.readFileSync(0, 'utf-8').trim().split(/\s+/);
    if (input.length < 2 || input[0] === "") return;
    
    const n = parseInt(input[0]);
    const m = parseInt(input[1]);
    const grid = input.slice(2, 2 + n);
    
    let sr = -1, sc = -1, er = -1, ec = -1;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < m; j++) {
            if (grid[i][j] === 'S') {
                sr = i; sc = j;
            } else if (grid[i][j] === 'E') {
                er = i; ec = j;
            }
        }
    }
    
    if (sr === -1 || er === -1) {
        console.log("-1");
        return;
    }
    
    const vis = Array.from({length: n}, () => 
        Array.from({length: m}, () => [false, false])
    );
    
    const q = [[sr, sc, 0, 0]];
    let head = 0;
    vis[sr][sc][0] = true;
    
    const dr = [-1, 1, 0, 0];
    const dc = [0, 0, -1, 1];
    
    while (head < q.length) {
        const [r, c, hasKey, steps] = q[head++];
        
        if (r === er && c === ec) {
            console.log(steps);
            return;
        }
        
        for (let i = 0; i < 4; i++) {
            const nr = r + dr[i];
            const nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                const cell = grid[nr][nc];
                if (cell === '#') continue;
                
                let nKey = hasKey;
                if (cell === 'k') nKey = 1;
                else if (cell === 'K' && hasKey === 0) continue;
                
                if (!vis[nr][nc][nKey]) {
                    vis[nr][nc][nKey] = true;
                    q.push([nr, nc, nKey, steps + 1]);
                }
            }
        }
    }
    
    console.log("-1");
}

solve();
