import sys
input = sys.stdin.readline

def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    vec = [1]
    ans = 0

    for i in range(1, n):
        if a[i] * 2 > a[i - 1]:
            vec[-1] += 1
        else:
            vec.append(1)

    for x in vec:
        ans += max(x - k, 0)

    print(ans)

solve()
