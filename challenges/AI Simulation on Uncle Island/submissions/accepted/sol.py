def solve():
    def get_input():
        import sys
        for line in sys.stdin:
            for word in line.split():
                yield word
    
    tokens = get_input()
    
    try:
        line1 = next(tokens)
    except StopIteration:
        return
        
    n = int(line1)
    p = []
    for _ in range(n):
        x = int(next(tokens))
        y = int(next(tokens))
        p.append((x, y))
        
    p.append(p[0])
    
    N = 2005
    oo = 2 * 10**18
    mod = 998244353
    
    in_grid = [[0] * N for _ in range(N)]
    add_grid = [[0] * N for _ in range(N)]
    window = [0] * N
    
    for i in range(1, n + 1):
        x, y = p[i]
        px, py = p[i - 1]
        
        min_y, max_y = (py, y) if py < y else (y, py)
        for j in range(min_y, max_y + 1):
            in_grid[x][j] = 1
            
        min_x, max_x = (px, x) if px < x else (x, px)
        for j in range(min_x, max_x + 1):
            in_grid[j][y] = 1
            
        for j in range(min_y, max_y):
            add_grid[x][j] = 1

    sources = []
    for x in range(N):
        for y in range(N):
            if in_grid[x][y]:
                sources.append((x, y))
            in_grid[x][y] |= window[y] & 1
            window[y] += add_grid[x][y]
            
    dist = [[oo] * N for _ in range(N)]
    

    q = []
    for x, y in sources:
        dist[x][y] = 0
        q.append((x, y))
        
    dx = (1, -1, 0, 0)
    dy = (0, 0, 1, -1)
    
    q_ptr = 0
    while q_ptr < len(q):
        x, y = q[q_ptr]
        q_ptr += 1
        d = dist[x][y]
        
        for k in range(4):
            nx, ny = x + dx[k], y + dy[k]
            if 0 <= nx < N and 0 <= ny < N:
                if dist[nx][ny] == oo and in_grid[nx][ny]:
                    dist[nx][ny] = d + 1
                    q.append((nx, ny))
                    
    vals = []
    for x in range(N):
        for y in range(N):
            if in_grid[x][y]:
                vals.append(dist[x][y])
                
    vals.sort()
    
    ans = 0
    pw = 1
    for v in vals:
        ans = (ans + v * pw) % mod
        pw = (pw * 2) % mod
        
    inv = pow((pw - 1) % mod, mod - 2, mod)
    print((ans * inv) % mod)

if __name__ == '__main__':
    solve()