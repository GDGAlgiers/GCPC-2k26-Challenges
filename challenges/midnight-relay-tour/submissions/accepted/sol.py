import heapq
import sys

INF = 10**30


def dijkstra(src, graph, n):
    dist = [INF] * (n + 1)
    dist[src] = 0
    pq = [(0, src)]

    while pq:
        d, u = heapq.heappop(pq)
        if d != dist[u]:
            continue
        for v, w in graph[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heapq.heappush(pq, (nd, v))

    return dist


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    it = iter(data)
    n = next(it)
    m = next(it)
    k = next(it)

    relays = [next(it) for _ in range(k)]

    graph = [[] for _ in range(n + 1)]
    for _ in range(m):
        u = next(it)
        v = next(it)
        w = next(it)
        graph[u].append((v, w))
        graph[v].append((u, w))

    important = [1] + relays + [n]
    count = len(important)
    dist_imp = [[INF] * count for _ in range(count)]

    for i, src in enumerate(important):
        dist = dijkstra(src, graph, n)
        for j, node in enumerate(important):
            dist_imp[i][j] = dist[node]

    if k == 0:
        ans = dist_imp[0][1]
        print(-1 if ans >= INF // 2 else ans)
        return

    size = 1 << k
    dp = [[INF] * k for _ in range(size)]
    for i in range(k):
        dp[1 << i][i] = dist_imp[0][i + 1]

    for mask in range(size):
        row = dp[mask]
        for i, cur in enumerate(row):
            if cur >= INF // 2:
                continue
            for j in range(k):
                if mask & (1 << j):
                    continue
                next_mask = mask | (1 << j)
                nd = cur + dist_imp[i + 1][j + 1]
                if nd < dp[next_mask][j]:
                    dp[next_mask][j] = nd

    full = size - 1
    ans = INF
    for i in range(k):
        ans = min(ans, dp[full][i] + dist_imp[i + 1][k + 1])

    print(-1 if ans >= INF // 2 else ans)


if __name__ == "__main__":
    main()
