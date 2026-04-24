// Accepted solution — Go
package main

import (
	"bufio"
	"fmt"
	"os"
)

var reader *bufio.Reader
var writer *bufio.Writer

type State struct {
	r, c, hasKey int
}

func main() {
	reader = bufio.NewReader(os.Stdin)
	writer = bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var n, m int
	if _, err := fmt.Fscan(reader, &n, &m); err != nil {
		fmt.Fprintln(writer, -1)
		return
	}

	grid := make([]string, n)
	sr, sc, er, ec := -1, -1, -1, -1
	for i := 0; i < n; i++ {
		fmt.Fscan(reader, &grid[i])
		for j := 0; j < m; j++ {
			switch grid[i][j] {
			case 'S':
				sr, sc = i, j
			case 'E':
				er, ec = i, j
			}
		}
	}

	if sr == -1 || er == -1 {
		fmt.Fprintln(writer, -1)
		return
	}

	vis := make([][][2]bool, n)
	for i := range vis {
		vis[i] = make([][2]bool, m)
	}

	queue := []State{{sr, sc, 0}}
	vis[sr][sc][0] = true
	steps := 0

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(queue) > 0 {
		size := len(queue)
		for i := 0; i < size; i++ {
			cur := queue[i]
			if cur.r == er && cur.c == ec {
				fmt.Fprintln(writer, steps)
				return
			}
			for d := 0; d < 4; d++ {
				nr, nc := cur.r+dr[d], cur.c+dc[d]
				if nr < 0 || nr >= n || nc < 0 || nc >= m {
					continue
				}
				cell := grid[nr][nc]
				if cell == '#' {
					continue
				}
				nKey := cur.hasKey
				if cell == 'k' {
					nKey = 1
				} else if cell == 'K' && cur.hasKey == 0 {
					continue
				}
				if !vis[nr][nc][nKey] {
					vis[nr][nc][nKey] = true
					queue = append(queue, State{nr, nc, nKey})
				}
			}
		}
		queue = queue[size:]
		steps++
	}

	fmt.Fprintln(writer, -1)
}
