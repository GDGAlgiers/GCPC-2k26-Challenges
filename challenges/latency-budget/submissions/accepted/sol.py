# Accepted solution — Python 3
import sys

input = sys.stdin.readline


def main():
    N, B = map(int, input().split())

    dp = [0] * (B + 1)
    dp[0] = 1

    for _ in range(N):
        line = list(map(int, input().split()))
        k = line[0]
        replicas = line[1:]
        ndp = [0] * (B + 1)
        for latency in replicas:
            for b in range(latency, B + 1):
                ndp[b] += dp[b - latency]
        dp = ndp

    print(sum(dp))


main()
