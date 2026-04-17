import sys


def solve():
    input_data = input().split()
    if not input_data: return
    n = int(input_data[0])
    d = int(input_data[1])

    p2 = [1 << i for i in range(n)]
    jump = [p2[j] * n + j for j in range(n)]

    adj = []
    for i in range(n):
        neighbors = []
        for j in range(max(0, i - d), min(n, i + d + 1)):
            if i != j:
                neighbors.append((p2[j], jump[j]))
        adj.append(neighbors)

    num_masks = 1 << n
    dp = [0] * (num_masks * n)

    for i in range(n):
        dp[p2[i] * n + i] = 1

    for mask in range(1, num_masks):
        m_off = mask * n
        for i in range(n):
            val = dp[m_off + i]
            if not val: continue

            for p2_j, jump_val in adj[i]:
                if not (mask & p2_j):
                    dp[m_off + jump_val] += val

    full_mask_off = (num_masks - 1) * n
    ans = sum(dp[full_mask_off: full_mask_off + n])
    sys.stdout.write(str(ans) + '\n')


if __name__ == '__main__':
    solve()