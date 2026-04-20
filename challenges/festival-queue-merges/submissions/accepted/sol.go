package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

type FastScanner struct {
	data []byte
	idx  int
	n    int
}

func NewFastScanner(r io.Reader) *FastScanner {
	b, _ := io.ReadAll(r)
	return &FastScanner{data: b, n: len(b)}
}

func (fs *FastScanner) next() string {
	for fs.idx < fs.n && fs.data[fs.idx] <= ' ' {
		fs.idx++
	}
	start := fs.idx
	for fs.idx < fs.n && fs.data[fs.idx] > ' ' {
		fs.idx++
	}
	return string(fs.data[start:fs.idx])
}

func (fs *FastScanner) nextInt64() int64 {
	for fs.idx < fs.n && fs.data[fs.idx] <= ' ' {
		fs.idx++
	}
	sign := int64(1)
	if fs.data[fs.idx] == '-' {
		sign = -1
		fs.idx++
	}
	var val int64
	for fs.idx < fs.n {
		c := fs.data[fs.idx]
		if c < '0' || c > '9' {
			break
		}
		val = val*10 + int64(c-'0')
		fs.idx++
	}
	return val * sign
}

type Node struct {
	c   int64
	neg int
}

func better(a, b Node) bool {
	if a.c != b.c {
		return a.c > b.c
	}
	return a.neg > b.neg
}

type MaxHeap struct {
	a []Node
}

func (h *MaxHeap) Push(v Node) {
	h.a = append(h.a, v)
	i := len(h.a) - 1
	for i > 0 {
		p := (i - 1) / 2
		if !better(h.a[i], h.a[p]) {
			break
		}
		h.a[i], h.a[p] = h.a[p], h.a[i]
		i = p
	}
}

func (h *MaxHeap) Pop() Node {
	ret := h.a[0]
	last := h.a[len(h.a)-1]
	h.a = h.a[:len(h.a)-1]
	if len(h.a) == 0 {
		return ret
	}
	h.a[0] = last
	i := 0
	for {
		l := 2*i + 1
		r := l + 1
		m := i
		if l < len(h.a) && better(h.a[l], h.a[m]) {
			m = l
		}
		if r < len(h.a) && better(h.a[r], h.a[m]) {
			m = r
		}
		if m == i {
			break
		}
		h.a[i], h.a[m] = h.a[m], h.a[i]
		i = m
	}
	return ret
}

func (h *MaxHeap) Top() Node {
	return h.a[0]
}

func main() {
	in := NewFastScanner(os.Stdin)
	out := bufio.NewWriterSize(os.Stdout, 1<<20)
	defer out.Flush()

	k := int(in.nextInt64())
	q := int(in.nextInt64())

	cnt := make([]int64, k+1)
	h := MaxHeap{a: make([]Node, 0, k+4*q+5)}
	for i := 1; i <= k; i++ {
		h.Push(Node{c: 0, neg: -i})
	}

	for i := 0; i < q; i++ {
		op := in.next()
		switch op {
		case "ADD":
			g := int(in.nextInt64())
			x := in.nextInt64()
			cnt[g] += x
			h.Push(Node{c: cnt[g], neg: -g})
		case "SERVE":
			g := int(in.nextInt64())
			x := in.nextInt64()
			t := x
			if cnt[g] < x {
				t = cnt[g]
			}
			cnt[g] -= t
			h.Push(Node{c: cnt[g], neg: -g})
		case "MOVE":
			a := int(in.nextInt64())
			b := int(in.nextInt64())
			x := in.nextInt64()
			t := x
			if cnt[a] < x {
				t = cnt[a]
			}
			cnt[a] -= t
			cnt[b] += t
			h.Push(Node{c: cnt[a], neg: -a})
			h.Push(Node{c: cnt[b], neg: -b})
		case "MERGE":
			a := int(in.nextInt64())
			b := int(in.nextInt64())
			cnt[a] += cnt[b]
			cnt[b] = 0
			h.Push(Node{c: cnt[a], neg: -a})
			h.Push(Node{c: cnt[b], neg: -b})
		default: // QUERY
			for {
				top := h.Top()
				idx := -top.neg
				if top.c == cnt[idx] {
					fmt.Fprintf(out, "%d %d\n", idx, top.c)
					break
				}
				h.Pop()
			}
		}
	}
}
