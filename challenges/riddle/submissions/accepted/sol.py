import sys

def solve():
    input = sys.stdin.readline
    n, d = map(int, input().split())
    mod = 10**9 + 7

    num_masks = 1 << n

    # Precompute neighbors
    adj = [[] for _ in range(n)]
    for i in range(n):
        L = max(0, i - d)
        R = min(n, i + d + 1)
        for j in range(L, R):
            if j != i:
                adj[i].append(j)

    # dp[mask][last]
    dp = [[0]*n for _ in range(num_masks)]

    # base cases
    for i in range(n):
        dp[1 << i][i] = 1

    for mask in range(num_masks):
        row = dp[mask]
        for last in range(n):
            val = row[last]
            if val == 0:
                continue

            for nxt in adj[last]:
                if not (mask & (1 << nxt)):
                    dp[mask | (1 << nxt)][nxt] += val
                    if dp[mask | (1 << nxt)][nxt] >= mod:
                        dp[mask | (1 << nxt)][nxt] -= mod

    full_mask = num_masks - 1
    print(sum(dp[full_mask]) % mod)

if __name__ == "__main__":
    solve()