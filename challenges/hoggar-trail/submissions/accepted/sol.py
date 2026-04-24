import sys


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return

    M = 10**9 + 7

    n = int(data[0])
    a = [int(x) for x in data[1 : n + 1]]

    unique_sorted = sorted(set(a))
    mp = {v: i + 1 for i, v in enumerate(unique_sorted)}
    sz = len(unique_sorted)

    pw = [0] * (n + 1)
    pw[0] = 1
    for i in range(1, n + 1):
        pw[i] = pw[i - 1] * 2 % M

    bit_cnt = [0] * (sz + 2)
    bit_sum = [0] * (sz + 2)

    def update(i, cv, sv):
        while i <= sz:
            bit_cnt[i] = (bit_cnt[i] + cv) % M
            bit_sum[i] = (bit_sum[i] + sv) % M
            i += i & (-i)

    def query(i):
        sc = ss = 0
        while i > 0:
            sc = (sc + bit_cnt[i]) % M
            ss = (ss + bit_sum[i]) % M
            i -= i & (-i)
        return sc, ss

    ans = 0
    total_cnt = 0
    total_sum = 0

    for i in range(n):
        x = a[i]
        idx = mp[x]

        lc, ls = query(idx - 1)
        tc, ts = query(idx)
        rc = (total_cnt - tc) % M
        rs = (total_sum - ts) % M

        cur = (lc * x - ls + rs - rc * x) % M
        ans = (ans + cur * pw[n - i - 1]) % M

        cv = pw[i]
        sv = x * pw[i] % M
        update(idx, cv, sv)
        total_cnt = (total_cnt + cv) % M
        total_sum = (total_sum + sv) % M

    print(ans % M)


if __name__ == "__main__":
    main()
