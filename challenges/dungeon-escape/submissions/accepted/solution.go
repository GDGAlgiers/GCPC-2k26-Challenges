package accepted

import (
	"fmt"
)

type Node struct {
	r, c, hasKey, steps int
}

func main() {
	var n, m int
	_, err := fmt.Scan(&n, &m)
	if err != nil {
		return
	}

	grid := make([]string, n)
	sr, sc, er, ec := -1, -1, -1, -1

	for i := 0; i < n; i++ {
		fmt.Scan(&grid[i])
		for j := 0; j < m; j++ {
			if grid[i][j] == 'S' {
				sr, sc = i, j
			} else if grid[i][j] == 'E' {
				er, ec = i, j
			}
		}
	}

	if sr == -1 || er == -1 {
		fmt.Println("-1")
		return
	}

	vis := make([][][]bool, n)
	for i := 0; i < n; i++ {
		vis[i] = make([][]bool, m)
		for j := 0; j < m; j++ {
			vis[i][j] = make([]bool, 2)
		}
	}

	q := []Node{{sr, sc, 0, 0}}
	vis[sr][sc][0] = true

	dr := []int{-1, 1, 0, 0}
	dc := []int{0, 0, -1, 1}

	for len(q) > 0 {
		curr := q[0]
		q = q[1:]

		if curr.r == er && curr.c == ec {
			fmt.Println(curr.steps)
			return
		}

		for i := 0; i < 4; i++ {
			nr, nc := curr.r+dr[i], curr.c+dc[i]

			if nr >= 0 && nr < n && nc >= 0 && nc < m {
				cell := grid[nr][nc]
				if cell == '#' {
					continue
				}

				nKey := curr.hasKey
				if cell == 'k' {
					nKey = 1
				} else if cell == 'K' && curr.hasKey == 0 {
					continue
				}

				if !vis[nr][nc][nKey] {
					vis[nr][nc][nKey] = true
					q = append(q, Node{nr, nc, nKey, curr.steps + 1})
				}
			}
		}
	}

	fmt.Println("-1")
}
