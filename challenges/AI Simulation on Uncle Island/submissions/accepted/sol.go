package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
)

const N = 2005
const oo int64 = 2e18
const mod int64 = 998244353

var in [N][N]int8
var add [N][N]int8
var dist [N][N]int64
var window [N]int

var dx = []int{1, -1, 0, 0}
var dy = []int{0, 0, 1, -1}

type Point struct {
	x, y int
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func power(a, b int64) int64 {
	var res int64 = 1
	a %= mod
	for b > 0 {
		if b&1 == 1 {
			res = (res * a) % mod
		}
		a = (a * a) % mod
		b >>= 1
	}
	return res
}

func valid(x, y int) bool {
	if x < 0 || y < 0 || x >= N || y >= N {
		return false
	}
	return in[x][y] != 0
}

func bfs(sources []Point) {
	for i := 0; i < N; i++ {
		for j := 0; j < N; j++ {
			dist[i][j] = oo
		}
	}

	q := make([]Point, 0, len(sources))
	for _, p := range sources {
		dist[p.x][p.y] = 0
		q = append(q, p)
	}

	head := 0
	for head < len(q) {
		p := q[head]
		head++

		for k := 0; k < 4; k++ {
			nx, ny := p.x+dx[k], p.y+dy[k]
			
			if nx >= 0 && nx < N && ny >= 0 && ny < N {
				if dist[nx][ny] < oo || !valid(nx, ny) {
					continue
				}
				dist[nx][ny] = dist[p.x][p.y] + 1
				q = append(q, Point{nx, ny})
			}
		}
	}
}

func magic(scanner *bufio.Scanner) {
	if !scanner.Scan() {
		return
	}
	n, _ := strconv.Atoi(scanner.Text())
	
	p := make([]Point, n)
	for i := 0; i < n; i++ {
		scanner.Scan()
		p[i].x, _ = strconv.Atoi(scanner.Text())
		scanner.Scan()
		p[i].y, _ = strconv.Atoi(scanner.Text())
	}
	p = append(p, p[0])

	for i := 1; i <= n; i++ {
		x, y := p[i].x, p[i].y
		px, py := p[i-1].x, p[i-1].y

		for j := min(py, y); j <= max(py, y); j++ {
			in[x][j] = 1
		}
		for j := min(px, x); j <= max(px, x); j++ {
			in[j][y] = 1
		}
		for j := min(py, y); j < max(py, y); j++ {
			add[x][j] = 1
		}
	}

	var sources []Point
	for x := 0; x < N; x++ {
		for y := 0; y < N; y++ {
			if in[x][y] != 0 {
				sources = append(sources, Point{x, y})
			}
			
			in[x][y] |= int8(window[y] & 1)
			window[y] += int(add[x][y])
		}
	}

	bfs(sources)

	var vals []int64
	for x := 0; x < N; x++ {
		for y := 0; y < N; y++ {
			if in[x][y] != 0 {
				vals = append(vals, dist[x][y])
			}
		}
	}

	sort.Slice(vals, func(i, j int) bool {
		return vals[i] < vals[j]
	})

	var ans int64 = 0
	var pw int64 = 1
	for i := 0; i < len(vals); i++ {
		ans = (ans + vals[i]%mod*pw) % mod
		pw = (pw * 2) % mod
	}

	inv := power((pw-1+mod)%mod, mod-2)
	res := (ans * inv) % mod
	fmt.Println(res)
}

func main() {
	// Fast I/O Setup
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanWords)
	
	buf := make([]byte, 0, 1024*1024)
	scanner.Buffer(buf, 10*1024*1024)

	magic(scanner)
}