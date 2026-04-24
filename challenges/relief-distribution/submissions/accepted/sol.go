package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

type FastScanner struct {
	r *bufio.Reader
}

func NewFastScanner() *FastScanner {
	return &FastScanner{r: bufio.NewReaderSize(os.Stdin, 1<<20)}
}

func (fs *FastScanner) NextInt() int {
	sign, val := 1, 0
	c, _ := fs.r.ReadByte()
	for (c < '0' || c > '9') && c != '-' {
		c, _ = fs.r.ReadByte()
	}
	if c == '-' {
		sign = -1
		c, _ = fs.r.ReadByte()
	}
	for c >= '0' && c <= '9' {
		val = val*10 + int(c-'0')
		c2, err := fs.r.ReadByte()
		if err != nil {
			return sign * val
		}
		c = c2
	}
	_ = fs.r.UnreadByte()
	return sign * val
}

type Job struct {
	d int
	w int
}

type MaxHeap struct {
	a []int
}

func (h *MaxHeap) Push(x int) {
	h.a = append(h.a, x)
	i := len(h.a) - 1
	for i > 0 {
		p := (i - 1) / 2
		if h.a[p] >= h.a[i] {
			break
		}
		h.a[p], h.a[i] = h.a[i], h.a[p]
		i = p
	}
}

func (h *MaxHeap) Pop() int {
	n := len(h.a)
	ret := h.a[0]
	n--
	h.a[0] = h.a[n]
	h.a = h.a[:n]
	i := 0
	for {
		l := 2*i + 1
		r := l + 1
		m := i
		if l < len(h.a) && h.a[l] > h.a[m] {
			m = l
		}
		if r < len(h.a) && h.a[r] > h.a[m] {
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

func (h *MaxHeap) Len() int {
	return len(h.a)
}

func main() {
	in := NewFastScanner()
	out := bufio.NewWriterSize(os.Stdout, 1<<20)
	defer out.Flush()

	n := in.NextInt()
	jobs := make([]Job, n)
	for i := 0; i < n; i++ {
		w := in.NextInt()
		d := in.NextInt()
		jobs[i] = Job{d: d, w: w}
	}

	sort.Slice(jobs, func(i, j int) bool {
		if jobs[i].d != jobs[j].d {
			return jobs[i].d < jobs[j].d
		}
		return jobs[i].w < jobs[j].w
	})

	h := MaxHeap{a: make([]int, 0, n)}
	total := int64(0)

	for _, job := range jobs {
		h.Push(job.w)
		total += int64(job.w)
		if h.Len() > job.d {
			total -= int64(h.Pop())
		}
	}

	fmt.Fprintf(out, "%d %d\n", h.Len(), total)
}
