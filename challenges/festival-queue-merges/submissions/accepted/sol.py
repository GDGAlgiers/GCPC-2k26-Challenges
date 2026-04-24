import heapq
import sys


def main() -> None:
    data = sys.stdin.buffer.read().split()
    if not data:
        return

    p = 0
    k = int(data[p]); p += 1
    q = int(data[p]); p += 1

    cnt = [0] * (k + 1)
    heap = []
    for i in range(1, k + 1):
        heap.append((0, i))
    heapq.heapify(heap)

    out = []

    for _ in range(q):
        op = data[p].decode(); p += 1

        if op == "ADD":
            g = int(data[p]); x = int(data[p + 1]); p += 2
            cnt[g] += x
            heapq.heappush(heap, (-cnt[g], g))
        elif op == "SERVE":
            g = int(data[p]); x = int(data[p + 1]); p += 2
            t = x if x < cnt[g] else cnt[g]
            cnt[g] -= t
            heapq.heappush(heap, (-cnt[g], g))
        elif op == "MOVE":
            a = int(data[p]); b = int(data[p + 1]); x = int(data[p + 2]); p += 3
            t = x if x < cnt[a] else cnt[a]
            cnt[a] -= t
            cnt[b] += t
            heapq.heappush(heap, (-cnt[a], a))
            heapq.heappush(heap, (-cnt[b], b))
        elif op == "MERGE":
            a = int(data[p]); b = int(data[p + 1]); p += 2
            cnt[a] += cnt[b]
            cnt[b] = 0
            heapq.heappush(heap, (-cnt[a], a))
            heapq.heappush(heap, (-cnt[b], b))
        else:
            while True:
                negc, idx = heap[0]
                c = -negc
                if c == cnt[idx]:
                    out.append(f"{idx} {c}")
                    break
                heapq.heappop(heap)

    sys.stdout.write("\n".join(out))
    if out:
        sys.stdout.write("\n")


if __name__ == "__main__":
    main()
