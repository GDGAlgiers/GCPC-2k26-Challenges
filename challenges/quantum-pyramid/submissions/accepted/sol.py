import sys

# Fast I/O setup
input = sys.stdin.read

def solve():
    # Read all input at once and split into a list of strings
    data = input().split()
    if not data:
        return
    
    ptr = 0
    n = int(data[ptr])
    Q = int(data[ptr + 1])
    ptr += 2
    
    # max_log = floor(log2(n)) + 1
    max_log = n.bit_length()
    
    # Sparse Table initialization
    # st[p][i] stores (classical_value, qubit_state)
    st = [[None] * (n + 1) for _ in range(max_log)]
    
    # Fill Level 0
    for i in range(1, n + 1):
        a = int(data[ptr])
        ptr += 1
        st[0][i] = (a // 2, a % 2)
        
    # Build Sparse Table
    for p in range(1, max_log):
        # Pre-calculating range limits and bit shifts for speed
        range_limit = n - (1 << p) + 1
        prev_level = st[p-1]
        offset = 1 << (p - 1)
        
        for i in range(1, range_limit + 1):
            # Inline the merge logic to avoid function call overhead
            a_c, a_q = prev_level[i]
            b_c, b_q = prev_level[i + offset]
            
            if a_c > b_c:
                st[p][i] = (a_c, a_q)
            elif a_c < b_c:
                st[p][i] = (b_c, b_q)
            elif a_q == b_q:
                st[p][i] = (a_c, a_q)
            else:
                st[p][i] = (a_c, 2) # Superposition

    # Process Queries
    results = []
    for _ in range(Q):
        k = int(data[ptr])
        r = int(data[ptr + 1])
        ptr += 2
        
        L = k
        R = k + r - 1
        
        # Calculate log2(length) using bit_length
        p = (R - L + 1).bit_length() - 1
        
        # Querying level p
        a_c, a_q = st[p][L]
        b_c, b_q = st[p][R - (1 << p) + 1]
        
        # Merge the two overlapping ranges
        res_c, res_q = 0, 0
        if a_c > b_c:
            res_c, res_q = a_c, a_q
        elif a_c < b_c:
            res_c, res_q = b_c, b_q
        elif a_q == b_q:
            res_c, res_q = a_c, a_q
        else:
            res_c, res_q = a_c, 2
            
        base_val = res_c * 2
        if res_q == 0:
            results.append(str(base_val))
        elif res_q == 1:
            results.append(str(base_val + 1))
        else:
            results.append(f"{base_val} {base_val + 1}")
            
    # Print all results at once for efficiency
    sys.stdout.write("\n".join(results) + "\n")

if __name__ == "__main__":
    solve()