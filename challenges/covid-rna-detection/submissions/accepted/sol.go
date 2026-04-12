// Accepted solution — Go
package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

var reader *bufio.Reader
var writer *bufio.Writer

func main() {
	reader = bufio.NewReader(os.Stdin)
	writer = bufio.NewWriter(os.Stdout)
	defer writer.Flush()

	var rna string
	fmt.Fscan(reader, &rna)

	markers := []string{"ACGUAUGC", "AUGCGUAG", "UGCUAGCU"}
	for _, m := range markers {
		if strings.Contains(rna, m) {
			fmt.Fprintln(writer, "True")
			return
		}
	}
	fmt.Fprintln(writer, "False")
}
