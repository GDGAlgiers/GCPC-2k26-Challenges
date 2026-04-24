import sys
from bisect import bisect_right, insort
from collections import defaultdict

def rev(x):
    res = 0
    for i in range(32):
        if x & (1 << i):
            res |= 1 << (31 - i)
    return res

def main():
    input = sys.stdin.read().split()
    ptr = 0
    q = int(input[ptr])
    ptr += 1

    # We'll use two lists to maintain sorted order
    list1 = []
    list2 = []
    sum1 = 0
    sum2 = 0
    bl = True  # state flag

    for _ in range(q):
        typ = int(input[ptr])
        ptr += 1

        if typ == 1:
            x = int(input[ptr])
            ptr += 1
            x2 = rev(x)

            if bl:
                insort(list1, x)
                insort(list2, x2)
                sum1 += x
                sum2 += x2
            else:
                insort(list2, x)
                insort(list1, x2)
                sum2 += x
                sum1 += x2

        elif typ == 2:
            if bl:
                if not list1:
                    continue
                mean = sum1 // len(list1)
                # Find the largest element <= mean
                idx = bisect_right(list1, mean) - 1
                val = list1[idx]
                print(val)
                sum1 -= val
                list1.pop(idx)

                x2 = rev(val)
                # Find and remove x2 from list2
                idx2 = bisect_right(list2, x2) - 1
                if idx2 >= 0 and list2[idx2] == x2:
                    sum2 -= list2[idx2]
                    list2.pop(idx2)
            else:
                if not list2:
                    continue
                mean = sum2 // len(list2)
                # Find the largest element <= mean
                idx = bisect_right(list2, mean) - 1
                val = list2[idx]
                print(val)
                sum2 -= val
                list2.pop(idx)

                x2 = rev(val)
                # Find and remove x2 from list1
                idx2 = bisect_right(list1, x2) - 1
                if idx2 >= 0 and list1[idx2] == x2:
                    sum1 -= list1[idx2]
                    list1.pop(idx2)

        elif typ == 3:
            bl = not bl

if __name__ == "__main__":
    main()
