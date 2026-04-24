import sys
import heapq


def main() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    n = data[0]
    boxes = []
    p = 1
    for _ in range(n):
        w = data[p]
        d = data[p + 1]
        p += 2
        boxes.append((d, w))

    boxes.sort()

    heap = []
    total = 0

    for d, w in boxes:
        heapq.heappush(heap, -w)
        total += w
        if len(heap) > d:
            total += heapq.heappop(heap)

    print(len(heap), total)


if __name__ == "__main__":
    main()
