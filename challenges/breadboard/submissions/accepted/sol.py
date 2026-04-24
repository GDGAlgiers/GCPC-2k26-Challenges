import sys

# Increase recursion depth for DSU path compression
sys.setrecursionlimit(200005)

def solve():
    # Fast I/O
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    N = int(input_data[0])
    M = int(input_data[1]) # M is read but not actively used in this logic, matching original C++
    Q = int(input_data[2])
    
    MOD = 10**9 + 7
    
    # Precompute powers of 2 for O(1) configuration calculation
    power2 = [0] * (N + 1)
    power2[0] = 1
    for i in range(1, N + 1):
        power2[i] = (power2[i - 1] * 2) % MOD
        
    # DSU initialization
    parent = list(range(N + 1))
    components = N
    
    def find(i):
        if parent[i] == i:
            return i
        parent[i] = find(parent[i]) # Path compression
        return parent[i]
        
    def unite(i, j):
        nonlocal components
        root_i = find(i)
        root_j = find(j)
        if root_i != root_j:
            parent[root_i] = root_j
            components -= 1

    # Track occupied holes using a Python set of tuples
    occupied = set()
    
    out = []
    idx = 3
    
    for _ in range(Q):
        r1 = int(input_data[idx])
        c1 = int(input_data[idx+1])
        r2 = int(input_data[idx+2])
        c2 = int(input_data[idx+3])
        idx += 4
        
        # Check if either hole is already occupied
        if (r1, c1) in occupied or (r2, c2) in occupied:
            # Discard cable, output current configuration
            out.append(str(power2[components]))
        else:
            # Mark holes as occupied and connect columns
            occupied.add((r1, c1))
            occupied.add((r2, c2))
            unite(c1, c2)
            out.append(str(power2[components]))
            
    # Print all outputs joined by a newline for fast I/O
    sys.stdout.write('\n'.join(out) + '\n')

if __name__ == '__main__':
    solve()
