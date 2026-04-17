import sys


def solve():
    input_data = input().split()
    if len(input_data) < 2:
        return

    n = int(input_data[0])
    d = int(input_data[1])
    mod = 10 ** 9 + 7

    adj = [[] for _ in range(n)]
    for i in range(n):
        for j in range(max(0, i - d), min(n, i + d + 1)):
            if i != j:
                adj[i].append(j)

    num_masks = 1 << n
    dp = [0] * (num_masks * n)

    for i in range(n):
        dp[(1 << i) * n + i] = 1

    for mask in range(1, num_masks):
        mask_offset = mask * n
        for i in range(n):
            if (mask >> i) & 1:
                prev_mask = mask ^ (1 << i)
                if prev_mask == 0:
                    continue

                prev_offset = prev_mask * n
                total_paths = 0
                for neighbor in adj[i]:
                    if (prev_mask >> neighbor) & 1:
                        total_paths += dp[prev_offset + neighbor]

                dp[mask_offset + i] = total_paths % mod

    full_mask_offset = (num_masks - 1) * n
    final_ans = sum(dp[full_mask_offset: full_mask_offset + n]) % mod
    sys.stdout.write(str(final_ans) + '\n')


if __name__ == '__main__':
    solve()