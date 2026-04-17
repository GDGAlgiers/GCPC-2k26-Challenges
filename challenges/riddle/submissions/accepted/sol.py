import sys


def solve():
    input_data = input().split()
    if not input_data: return
    n, d = int(input_data[0]), int(input_data[1])
    mod = 10 ** 9 + 7

    adj = []
    for i in range(n):
        neighbors = []
        for j in range(max(0, i - d), min(n, i + d + 1)):
            if i != j:
                neighbors.append(j)
        adj.append(neighbors)

    num_masks = 1 << n
    dp = [0] * (num_masks * n)

    for i in range(n):
        dp[(1 << i) * n + i] = 1

    for mask in range(1, num_masks):
        m_off = mask * n
        for i in range(n):
            if (mask >> i) & 1:
                prev_mask = mask ^ (1 << i)
                if prev_mask == 0: continue

                p_off = prev_mask * n
                total = 0
                for neighbor in adj[i]:
                    total += dp[p_off + neighbor]

                dp[m_off + i] = total % mod

    full_mask_off = (num_masks - 1) * n
    ans = sum(dp[full_mask_off: full_mask_off + n]) % mod
    sys.stdout.write(str(ans) + '\n')


if __name__ == '__main__':
    solve()