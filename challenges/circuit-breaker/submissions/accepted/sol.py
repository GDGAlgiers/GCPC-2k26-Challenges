# Accepted solution — Python 3
import sys

input = sys.stdin.readline


def main():
    N, W, X, C = map(int, input().split())
    E = int(input())

    # per-service failure timestamps (only failures, sorted)
    failures = [[] for _ in range(N)]

    for _ in range(E):
        T, S, R = map(int, input().split())
        if R == 0:
            failures[S].append(T)

    # simulate circuit breaker per service, record open intervals
    # each interval is (open_time, open_time + C)
    intervals = [[] for _ in range(N)]

    for s in range(N):
        fl = failures[s]
        left = 0
        skip_until = -1  # events before this time are inside an open interval

        i = 0
        valid = []  # failures not inside any open interval
        while i < len(fl):
            t = fl[i]
            if t < skip_until:
                i += 1
                continue
            valid.append(t)
            # check if window accumulated X failures
            # window is [t - W, t]
            while valid and valid[0] < t - W:
                valid.pop(0)
            if len(valid) == X:
                open_time = t
                close_time = open_time + C
                intervals[s].append((open_time, close_time))
                skip_until = close_time
                valid = []
            i += 1

    # intervals per service are sorted by open_time (simulation order)
    # answer queries
    Q = int(input())
    out = []
    for _ in range(Q):
        T, S = map(int, input().split())
        ivs = intervals[S]
        # binary search: find the last interval with open_time <= T
        lo, hi = 0, len(ivs) - 1
        found = False
        while lo <= hi:
            mid = (lo + hi) // 2
            if ivs[mid][0] <= T:
                if ivs[mid][1] > T:
                    found = True
                    break
                lo = mid + 1
            else:
                hi = mid - 1
        out.append("OPEN" if found else "CLOSED")

    print("\n".join(out))


main()
