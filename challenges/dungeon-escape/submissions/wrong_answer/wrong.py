import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    N = int(input_data[0])
    M = int(input_data[1])
    grid = input_data[2:]
    
    start = None
    exit_pos = None
    
    for i in range(N):
        for j in range(M):
            if grid[i][j] == 'S':
                start = (i, j)
            elif grid[i][j] == 'E':
                exit_pos = (i, j)
                
    if not start or not exit_pos:
        print("-1")
        return
        
    q = deque()
    q.append((start[0], start[1]))
    
    visited = [[False]*M for _ in range(N)]
    visited[start[0]][start[1]] = True
    
    steps = 0
    dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while q:
        size = len(q)
        for _ in range(size):
            r, c = q.popleft()
            
            if (r, c) == exit_pos:
                print(steps)
                return
                
            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < N and 0 <= nc < M:
                    cell = grid[nr][nc]
                    # Wrong Logic: Treating K as a wall
                    if cell == '#' or cell == 'K':
                        continue
                        
                    if not visited[nr][nc]:
                        visited[nr][nc] = True
                        q.append((nr, nc))
        steps += 1
        
    print("-1")

if __name__ == '__main__':
    solve()
