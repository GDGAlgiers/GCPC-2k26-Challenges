package main

import (
    "bufio"
    "fmt"
    "os"
    "sort"
)

func rev(x uint32) uint32 {
    var res uint32 = 0
    for i := 0; i < 32; i++ {
        if x&(1<<i) != 0 {
            res |= 1 << (31 - i)
        }
    }
    return res
}

type SortedList struct {
    data []uint32
}

func (sl *SortedList) Insert(x uint32) {
    i := sort.Search(len(sl.data), func(i int) bool { return sl.data[i] >= x })
    sl.data = append(sl.data, 0)
    copy(sl.data[i+1:], sl.data[i:])
    sl.data[i] = x
}

func (sl *SortedList) Remove(x uint32) bool {
    i := sort.Search(len(sl.data), func(i int) bool { return sl.data[i] >= x })
    if i < len(sl.data) && sl.data[i] == x {
        sl.data = append(sl.data[:i], sl.data[i+1:]...)
        return true
    }
    return false
}

func (sl *SortedList) UpperBound(x uint32) int {
    return sort.Search(len(sl.data), func(i int) bool { return sl.data[i] > x })
}

func (sl *SortedList) Get(i int) uint32 {
    return sl.data[i]
}

func (sl *SortedList) Len() int {
    return len(sl.data)
}

func (sl *SortedList) Sum() uint64 {
    var sum uint64 = 0
    for _, v := range sl.data {
        sum += uint64(v)
    }
    return sum
}

func main() {
    reader := bufio.NewReader(os.Stdin)
    writer := bufio.NewWriter(os.Stdout)
    defer writer.Flush()

    var q int
    fmt.Fscan(reader, &q)

    list1 := &SortedList{}
    list2 := &SortedList{}
    var sum1, sum2 uint64 = 0, 0
    bl := true

    for i := 0; i < q; i++ {
        var typ int
        fmt.Fscan(reader, &typ)

        if typ == 1 {
            var x uint32
            fmt.Fscan(reader, &x)
            x2 := rev(x)

            if bl {
                list1.Insert(x)
                list2.Insert(x2)
                sum1 += uint64(x)
                sum2 += uint64(x2)
            } else {
                list2.Insert(x)
                list1.Insert(x2)
                sum2 += uint64(x)
                sum1 += uint64(x2)
            }
        } else if typ == 2 {
            if bl {
                if list1.Len() == 0 {
                    continue
                }
                mean := sum1 / uint64(list1.Len())
                idx := list1.UpperBound(uint32(mean)) - 1
                val := list1.Get(idx)
                fmt.Fprintln(writer, val)
                sum1 -= uint64(val)
                list1.Remove(val)

                x2 := rev(val)
                sum2 -= uint64(x2)
                list2.Remove(x2)
            } else {
                if list2.Len() == 0 {
                    continue
                }
                mean := sum2 / uint64(list2.Len())
                idx := list2.UpperBound(uint32(mean)) - 1
                val := list2.Get(idx)
                fmt.Fprintln(writer, val)
                sum2 -= uint64(val)
                list2.Remove(val)

                x2 := rev(val)
                sum1 -= uint64(x2)
                list1.Remove(x2)
            }
        } else if typ == 3 {
            bl = !bl
        }
    }
}
