package main

import (
    "bufio"
    "fmt"
    "os"
)

func main() {
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    var N int
    if _, err := fmt.Fscan(in, &N); err != nil {
        return
    }

    var mat [20][20]int

    for i := 0; i < N; i++ {
        for j := 0; j < N; j++ {
            fmt.Fscan(in, &mat[i][j])
        }
    }

    best := N

    for mask := 0; mask < (1 << N); mask++ {
        covered := [20]int{}
        count := 0

        for i := 0; i < N; i++ {
            if mask&(1<<i) != 0 {
                count++
                covered[i] = 1

                for j := 0; j < N; j++ {
                    if mat[i][j] == 1 {
                        covered[j] = 1
                    }
                }
            }
        }

        ok := true
        for i := 0; i < N; i++ {
            if covered[i] == 0 {
                ok = false
                break
            }
        }

        if ok && count < best {
            best = count
        }
    }

    fmt.Fprintln(out, best)
}
