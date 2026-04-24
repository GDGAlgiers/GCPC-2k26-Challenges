package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

const M int64 = 1000000007
const N = 100010

var pw [N]int64

func add(a, b int64) int64 {
	return (a + b) % M
}

func mul(a, b int64) int64 {
	return (a * b) % M
}

func sub(a, b int64) int64 {
	return ((a - b) % M + M) % M
}

type Node struct {
	cnt int64
	sum int64
}

var neutral = Node{0, 0}

type SegTree struct {
	left  *SegTree
	right *SegTree
	node  Node
	start int
	end   int
}

func NewSegTree(l, r int) *SegTree {
	return &SegTree{
		start: l,
		end:   r,
	}
}

func (st *SegTree) extend() {
	if st.left == nil {
		mid := st.start + (st.end-st.start)/2
		st.left = NewSegTree(st.start, mid)
		st.right = NewSegTree(mid+1, st.end)
	}
}

func pushup(a, b Node) Node {
	return Node{
		cnt: add(a.cnt, b.cnt),
		sum: add(a.sum, b.sum),
	}
}

func (st *SegTree) update(idx int, sum, cnt int64) {
	if st.start > idx || st.end < idx {
		return
	}
	if st.start == st.end {
		st.node.cnt = add(st.node.cnt, cnt)
		st.node.sum = add(st.node.sum, sum)
		return
	}
	st.extend()
	st.left.update(idx, sum, cnt)
	st.right.update(idx, sum, cnt)
	st.node = pushup(st.left.node, st.right.node)
}

func (st *SegTree) query(l, r int) Node {
	if r < st.start || st.end < l {
		return neutral
	}
	if l <= st.start && st.end <= r {
		return st.node
	}
	st.extend()
	return pushup(st.left.query(l, r), st.right.query(l, r))
}

func solve(in *bufio.Reader) {
	var n int
	if _, err := fmt.Fscan(in, &n); err != nil {
		return
	}

	a := make([]int64, n)
	mp := make(map[int64]int)
	unique := make([]int64, 0)

	for i := 0; i < n; i++ {
		fmt.Fscan(in, &a[i])
		if mp[a[i]] == 0 {
			mp[a[i]] = 1
			unique = append(unique, a[i])
		}
	}

	// Coordinate Compression
	sort.Slice(unique, func(i, j int) bool { return unique[i] < unique[j] })

	nxt := 1
	for _, val := range unique {
		mp[val] = nxt
		nxt++
	}

	root := NewSegTree(0, nxt+5)
	var ans int64 = 0

	for i := 0; i < n; i++ {
		x := a[i]
		mappedIdx := mp[x]

		left := root.query(0, mappedIdx-1)
		right := root.query(mappedIdx+1, nxt+5)

		cur := sub(mul(left.cnt, x), left.sum)
		cur = add(cur, sub(right.sum, mul(right.cnt, x)))

		ans = add(ans, mul(cur, pw[n-i-1]))
		root.update(mappedIdx, mul(x, pw[i]), pw[i])
	}

	fmt.Println(ans)
}

func main() {
	pw[0] = 1
	for i := 1; i < N; i++ {
		pw[i] = (pw[i-1] << 1) % M
	}

	in := bufio.NewReader(os.Stdin)

	tc := 1
	// fmt.Fscan(in, &tc)
	for t := 0; t < tc; t++ {
		solve(in)
	}
}