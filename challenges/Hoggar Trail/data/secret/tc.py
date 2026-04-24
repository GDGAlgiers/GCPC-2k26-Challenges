import os
import random

MOD = 10**9 + 7

def solve_logic(n, a):
    """Reference O(N log N) solution to generate the .ans files."""
    if n < 2:
        return 0
    coords = sorted(list(set(a)))
    rank = {val: i + 1 for i, val in enumerate(coords)}
    m = len(coords)
    pow2 = [1] * (n + 1)
    for i in range(1, n + 1):
        pow2[i] = (pow2[i-1] * 2) % MOD
    bit_count = [0] * (m + 1)
    bit_val_sum = [0] * (m + 1)

    def update(bit, idx, val):
        while idx <= m:
            bit[idx] = (bit[idx] + val) % MOD
            idx += idx & (-idx)
    def query(bit, idx):
        res = 0
        while idx > 0:
            res = (res + bit[idx]) % MOD
            idx -= idx & (-idx)
        return res

    total_effort = 0
    for j in range(n):
        val, r = a[j], rank[a[j]]
        c_low, s_low = query(bit_count, r), query(bit_val_sum, r)
        c_all, s_all = query(bit_count, m), query(bit_val_sum, m)
        
        term_low = (val * c_low - s_low) % MOD
        term_high = ((s_all - s_low) - val * (c_all - c_low)) % MOD
        
        total_effort = (total_effort + (term_low + term_high) * pow2[n - 1 - j]) % MOD
        update(bit_count, r, pow2[j])
        update(bit_val_sum, r, (val * pow2[j]) % MOD)
    return total_effort % MOD

def write_test(idx, n, a):
    prefix = f"{idx:02d}"
    with open(f"{prefix}.in", "w") as f:
        f.write(f"{n}\n")
        f.write(" ".join(map(str, a)) + "\n")
    ans = solve_logic(n, a)
    with open(f"{prefix}.ans", "w") as f:
        f.write(f"{ans}\n")
    print(f"Generated {prefix}.in and {prefix}.ans")

def main():
    # 01-02: Small but tricky (Negative values & large ranges)
    write_test(1, 10, [random.randint(-10**9, 10**9) for _ in range(10)])
    write_test(2, 50, [i * (-1)**i for i in range(50)])

    # 03-04: Constant and Nearly Constant (Stress tests for 0 effort)
    write_test(3, 10**5, [10**9] * 10**5)
    write_test(4, 10**5, [random.randint(0, 1) for _ in range(10**5)])

    # 05-06: Massive Monotonic (Increasing/Decreasing)
    write_test(5, 10**5, list(range(-50000, 50000)))
    write_test(6, 10**5, list(range(10**9, 10**9 - 100000, -1)))

    # 07-08: Alternating Extremes (Max oscillation)
    write_test(7, 10**5, [10**9 if i % 2 == 0 else -10**9 for i in range(10**5)])
    write_test(8, 10**5, [random.choice([-10**9, 0, 10**9]) for _ in range(10**5)])

    # 09-10: Huge Random (The ultimate performance test)
    write_test(9, 10**5, [random.randint(-10**9, 10**9) for _ in range(10**5)])
    write_test(10, 10**5, [random.randint(-10**9, 10**9) for _ in range(10**5)])

    # 11-12: Specific Patterns (Arithmetic and Clustered)
    write_test(11, 10**5, [i * 10000 for i in range(10**5)]) # Large jumps
    write_test(12, 10**5, [random.randint(100, 200) for _ in range(10**5)]) # High collision

if __name__ == "__main__":
    main()