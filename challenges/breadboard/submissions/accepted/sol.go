package main

import (
    "bufio"
    "fmt"
    "os"
)

const MOD = 1e9 + 7

// DSU struct to handle Disjoint Set Union operations
type DSU struct {
    parent     []int
    components int
}

func NewDSU(n int) *DSU {
    parent := make([]int, n+1)
    for i := 1; i <= n; i++ {
        parent[i] = i
    }
    return &DSU{
        parent:     parent,
        components: n,
    }
}

func (d *DSU) Find(i int) int {
    if d.parent[i] == i {
        return i
    }
    // Path compression
    d.parent[i] = d.Find(d.parent[i])
    return d.parent[i]
}

func (d *DSU) Unite(i, j int) {
    rootI := d.Find(i)
    rootJ := d.Find(j)
    if rootI != rootJ {
        d.parent[rootI] = rootJ
        d.components--
    }
}

// Point struct acts similarly to std::pair<int, int> in C++
type Point struct {
    r, c int
}

func main() {
    // Setup fast I/O
    reader := bufio.NewReader(os.Stdin)
    writer := bufio.NewWriter(os.Stdout)
    defer writer.Flush()

    var N, M, Q int
    if _, err := fmt.Fscan(reader, &N, &M, &Q); err != nil {
        return // Exit if reading fails
    }

    // Precompute powers of 2 for O(1) configuration calculation
    power2 := make([]int64, N+1)
    power2[0] = 1
    for i := 1; i <= N; i++ {
        power2[i] = (power2[i-1] * 2) % MOD
    }

    dsu := NewDSU(N)
    
    // Track occupied holes using a map with a Point struct as the key
    occupied := make(map[Point]bool)

    for i := 0; i < Q; i++ {
        var r1, c1, r2, c2 int
        fmt.Fscan(reader, &r1, &c1, &r2, &c2)

        p1 := Point{r1, c1}
        p2 := Point{r2, c2}

        // Check if either hole is already occupied
        if occupied[p1] || occupied[p2] {
            // Discard cable, output current configuration
            fmt.Fprintln(writer, power2[dsu.components])
        } else {
            // Mark holes as occupied and connect columns
            occupied[p1] = true
            occupied[p2] = true
            dsu.Unite(c1, c2)
            fmt.Fprintln(writer, power2[dsu.components])
        }
    }
}
