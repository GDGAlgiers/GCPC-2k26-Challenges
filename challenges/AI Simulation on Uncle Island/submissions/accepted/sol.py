import sys

def get_input():
    # Keeping your original reading method
    for line in sys.stdin:
        for word in line.split():
            yield word

def solve():
    tokens = get_input()
    
    try:
        line1 = next(tokens)
    except StopIteration:
        return
        
    n = int(line1)
    p = []
    min_x, max_x = 2005, 0
    min_y, max_y = 2005, 0
    
    for _ in range(n):
        x = int(next(tokens))
        y = int(next(tokens))
        p.append((x, y))
        if x < min_x: min_x = x
        if x > max_x: max_x = x
        if y < min_y: min_y = y
        if y > max_y: max_y = y

    # Use a bounding box to save time
    limit_x = max_x + 2
    limit_y = max_y + 2
    oo = 10**9
    mod = 998244353
    
    # in_grid[x][y] == 1 if point is part of polygon (boundary or interior)
    # is_boundary[x][y] == 1 if point is exactly on the edge
    in_grid = [[0] * limit_y for _ in range(limit_x)]
    is_boundary = [[0] * limit_y for _ in range(limit_x)]
    
    # Mark edges for the scanline toggle
    # We use vertical segments to determine interior
    edge_toggle = [[0] * limit_y for _ in range(limit_x)]
    
    for i in range(n):
        x1, y1 = p[i]
        x2, y2 = p[(i + 1) % n]
        
        if x1 == x2: # Vertical
            y_start, y_end = (y1, y2) if y1 < y2 else (y2, y1)
            for y in range(y_start, y_end + 1):
                is_boundary[x1][y] = 1
            # Toggle logic: mark the range (x, y_start) to (x, y_end-1)
            for y in range(y_start, y_end):
                edge_toggle[x1][y] ^= 1
        else: # Horizontal
            x_start, x_end = (x1, x2) if x1 < x2 else (x2, x1)
            for x in range(x_start, x_end + 1):
                is_boundary[x][y1] = 1

    # Fill interior using Even-Odd rule
    for y in range(min_y, max_y + 1):
        inside = 0
        for x in range(min_x, max_x + 1):
            if edge_toggle[x][y]:
                inside ^= 1
            if inside or is_boundary[x][y]:
                in_grid[x][y] = 1

    # Initialize Distance Grid
    # Distance is 0 for boundary, oo for interior, -1 for outside
    dist = [[-1] * limit_y for _ in range(limit_x)]
    for x in range(min_x, max_x + 1):
        for y in range(min_y, max_y + 1):
            if in_grid[x][y]:
                dist[x][y] = 0 if is_boundary[x][y] else oo

    # Two-Pass Distance Transform (Faster than BFS in Python)
    # Top-Left to Bottom-Right
    for x in range(min_x, max_x + 1):
        for y in range(min_y, max_y + 1):
            if dist[x][y] > 0:
                d = dist[x][y]
                if x > 0 and dist[x-1][y] != -1: d = min(d, dist[x-1][y] + 1)
                if y > 0 and dist[x][y-1] != -1: d = min(d, dist[x][y-1] + 1)
                dist[x][y] = d
                
    # Bottom-Right to Top-Left
    for x in range(max_x, min_x - 1, -1):
        for y in range(max_y, min_y - 1, -1):
            if dist[x][y] > 0:
                d = dist[x][y]
                if x < limit_x - 1 and dist[x+1][y] != -1: d = min(d, dist[x+1][y] + 1)
                if y < limit_y - 1 and dist[x][y+1] != -1: d = min(d, dist[x][y+1] + 1)
                dist[x][y] = d

    # Counting Sort (Much faster than vals.sort())
    max_d = limit_x + limit_y
    freq = [0] * (max_d + 1)
    for x in range(min_x, max_x + 1):
        for y in range(min_y, max_y + 1):
            if dist[x][y] >= 0:
                freq[dist[x][y]] += 1
    
    ans = 0
    pw = 1
    for d in range(max_d + 1):
        f = freq[d]
        if f == 0: continue
        # We need to process each instance of distance 'd'
        for _ in range(f):
            ans = (ans + d * pw) % mod
            pw = (pw * 2) % mod
            
    inv = pow((pw - 1) % mod, mod - 2, mod)
    print((ans * inv) % mod)

if __name__ == '__main__':
    solve()