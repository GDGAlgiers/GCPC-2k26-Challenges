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

    graph = [[] for _ in range(n + 1)]
    roads = []
    for _ in range(m):
        u = next(it)
        v = next(it)
        w = next(it)
        graph[u].append((v, w))
        graph[v].append((u, w))
        roads.append((u, v))

    dist_start = dijkstra(1, graph, n)
    dist_end = dijkstra(n, graph, n)

    ans = dist_start[n]
    for u, v in roads:
        if dist_start[u] < INF // 2 and dist_end[v] < INF // 2:
            ans = min(ans, dist_start[u] + dist_end[v])
        if dist_start[v] < INF // 2 and dist_end[u] < INF // 2:
            ans = min(ans, dist_start[v] + dist_end[u])

    print(-1 if ans >= INF // 2 else ans)


if __name__ == "__main__":
    main()
