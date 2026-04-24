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

type Road struct {
	u int
	v int
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

func main() {
	in := bufio.NewReaderSize(os.Stdin, 1<<20)
	var n, m int
	if _, err := fmt.Fscan(in, &n, &m); err != nil {
		return
	}

	graph := make([][]Edge, n+1)
	roads := make([]Road, 0, m)

	for i := 0; i < m; i++ {
		var u, v int
		var w int64
		fmt.Fscan(in, &u, &v, &w)
		graph[u] = append(graph[u], Edge{to: v, w: w})
		graph[v] = append(graph[v], Edge{to: u, w: w})
		roads = append(roads, Road{u: u, v: v})
	}

	distStart := dijkstra(1, graph)
	distEnd := dijkstra(n, graph)

	ans := distStart[n]
	for _, road := range roads {
		if distStart[road.u] < INF/2 && distEnd[road.v] < INF/2 {
			if val := distStart[road.u] + distEnd[road.v]; val < ans {
				ans = val
			}
		}
		if distStart[road.v] < INF/2 && distEnd[road.u] < INF/2 {
			if val := distStart[road.v] + distEnd[road.u]; val < ans {
				ans = val
			}
		}
	}

	if ans >= INF/2 {
		fmt.Println(-1)
	} else {
		fmt.Println(ans)
	}
}
