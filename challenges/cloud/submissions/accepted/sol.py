from functools import lru_cache

@lru_cache(maxsize=None)
def sz(n, k):
    if k > n: return 0
    if n == 1: return 1
    if n % 2 == 0: return 2 * sz(n // 2, k)
    else: return 1 + 2 * sz(n // 2, k)

@lru_cache(maxsize=None)
def f(n, k):
    if k > n: return 0
    if n == 1: return 1
    if n % 2 == 0: return 2 * f(n // 2, k) + (n // 2) * sz(n // 2, k)
    else: return ((n + 1) // 2) + 2 * f(n // 2, k) + ((n + 1) // 2) * sz(n // 2, k)

n, k = map(int, input().split())
N, K = map(int, input().split())

Raouf = f(n, k)
Hachem = f(N, K)

if Raouf > Hachem:
    print("Raouf")
elif Raouf < Hachem:
    print("Hachem")
else:
    print("Tie")