// Accepted solution — Go
// Replace this with the actual correct solution.
package main

import (
	"bufio"
	"os"
)

var reader *bufio.Reader
var writer *bufio.Writer

func main() {
	reader = bufio.NewReader(os.Stdin)
	writer = bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	// TODO: read input and solve
}
