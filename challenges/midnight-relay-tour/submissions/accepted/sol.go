package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
)

const INF int64 = 4_000_000_000_000_000_000

type Edge struct {
	to int
	w  int64
}

type Item struct {
	dist int64
	node int
}

type MinHeap []Item

func (h MinHeap) Len() int           { return len(h) }
func (h MinHeap) Less(i, j int) bool { return h[i].dist < h[j].dist }
func (h MinHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *MinHeap) Push(x any) {
	*h = append(*h, x.(Item))
}

func (h *MinHeap) Pop() any {
	old := *h
	n := len(old)
	item := old[n-1]
	*h = old[:n-1]
	return item
}

func dijkstra(src int, graph [][]Edge) []int64 {
	n := len(graph) - 1
	dist := make([]int64, n+1)
	for i := range dist {
		dist[i] = INF
	}
	dist[src] = 0

	pq := &MinHeap{{dist: 0, node: src}}
	heap.Init(pq)

	for pq.Len() > 0 {
		cur := heap.Pop(pq).(Item)
		if cur.dist != dist[cur.node] {
			continue
		}
		for _, e := range graph[cur.node] {
			nd := cur.dist + e.w
			if nd < dist[e.to] {
				dist[e.to] = nd
				heap.Push(pq, Item{dist: nd, node: e.to})
			}
		}
	}

	return dist
}

func min(a, b int64) int64 {
	if a < b {
		return a
	}
	return b
}

func main() {
	in := bufio.NewReaderSize(os.Stdin, 1<<20)

	var n, m, k int
	if _, err := fmt.Fscan(in, &n, &m, &k); err != nil {
		return
	}

	relays := make([]int, k)
	for i := 0; i < k; i++ {
		fmt.Fscan(in, &relays[i])
	}

	graph := make([][]Edge, n+1)
	for i := 0; i < m; i++ {
		var u, v int
		var w int64
		fmt.Fscan(in, &u, &v, &w)
		graph[u] = append(graph[u], Edge{to: v, w: w})
		graph[v] = append(graph[v], Edge{to: u, w: w})
	}

	important := make([]int, 0, k+2)
	important = append(important, 1)
	important = append(important, relays...)
	important = append(important, n)

	cnt := len(important)
	distImp := make([][]int64, cnt)
	for i := range distImp {
		distImp[i] = make([]int64, cnt)
		for j := range distImp[i] {
			distImp[i][j] = INF
		}
	}

	for i, src := range important {
		dist := dijkstra(src, graph)
		for j, node := range important {
			distImp[i][j] = dist[node]
		}
	}

	if k == 0 {
		ans := distImp[0][1]
		if ans >= INF/2 {
			fmt.Println(-1)
		} else {
			fmt.Println(ans)
		}
		return
	}

	size := 1 << k
	dp := make([][]int64, size)
	for mask := range dp {
		dp[mask] = make([]int64, k)
		for i := range dp[mask] {
			dp[mask][i] = INF
		}
	}

	for i := 0; i < k; i++ {
		dp[1<<i][i] = distImp[0][i+1]
	}

	for mask := 0; mask < size; mask++ {
		for i := 0; i < k; i++ {
			cur := dp[mask][i]
			if cur >= INF/2 {
				continue
			}
			for j := 0; j < k; j++ {
				if mask&(1<<j) != 0 {
					continue
				}
				nextMask := mask | (1 << j)
				nd := cur + distImp[i+1][j+1]
				if nd < dp[nextMask][j] {
					dp[nextMask][j] = nd
				}
			}
		}
	}

	full := size - 1
	ans := INF
	for i := 0; i < k; i++ {
		ans = min(ans, dp[full][i]+distImp[i+1][k+1])
	}

	if ans >= INF/2 {
		fmt.Println(-1)
	} else {
		fmt.Println(ans)
	}
}
