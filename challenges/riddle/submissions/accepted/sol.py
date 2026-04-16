import sys


def solve():
    input_data = input().split()

    if not input_data:
        return

    # Ensure we have at least N and D
    if len(input_data) < 2:
        return

    n = int(input_data[0])
    d = int(input_data[1])
    mod = 10 ** 9 + 7

    # DP table: dp[mask][last_index]
    dp = [[0] * n for _ in range(1 << n)]

    # Base case: Each single element is a valid starting point
    for i in range(n):
        dp[1 << i][i] = 1

    # Precompute adjacency masks for each index i
    # adj_mask[i] contains a 1 at bit j if |i - j| <= d
    adj_mask = [0] * n
    for i in range(n):
        for j in range(max(i - d, 0), i):
            adj_mask[i] |= (1 << j)
        for j in range(i + 1, min(i + d, n - 1) + 1):
            adj_mask[i] |= (1 << j)

    # Iterate through all bitmasks
    for mask in range(1, 1 << n):
        for i in range(n):
            # If the current mask doesn't include i or we have no paths ending at i
            if not (mask & (1 << i)) or dp[mask][i] == 0:
                continue

            # Find neighbors of i that are NOT in the current mask
            cur = adj_mask[i] & (~mask)
            while cur > 0:
                # Get index of the lowest set bit (trailing zero count)
                # This mimics __builtin_ctz from C++
                lowest_bit = cur & -cur
                idx = lowest_bit.bit_length() - 1

                next_mask = mask | (1 << idx)
                dp[next_mask][idx] = (dp[next_mask][idx] + dp[mask][i]) % mod

                # Clear the lowest set bit to move to the next neighbor
                cur ^= lowest_bit

    # The answer is the sum of all paths that visit every node (full mask)
    ans = 0
    full_mask = (1 << n) - 1
    for i in range(n):
        ans = (ans + dp[full_mask][i]) % mod

    sys.stdout.write(str(ans) + '\n')


if __name__ == '__main__':
    solve()