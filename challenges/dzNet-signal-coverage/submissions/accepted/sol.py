import sys


def main() -> None:
    data = list(map(int, sys.stdin.buffer.read().split()))
    if not data:
        return

    ptr = 0
    n = data[ptr]
    ptr += 1

    mat = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            mat[i][j] = data[ptr]
            ptr += 1

    best = n

    for mask in range(1 << n):
        covered = [0] * n
        count = 0

        for i in range(n):
            if mask & (1 << i):
                count += 1
                covered[i] = 1

                for j in range(n):
                    if mat[i][j] == 1:
                        covered[j] = 1

        ok = True
        for i in range(n):
            if covered[i] == 0:
                ok = False
                break

        if ok and count < best:
            best = count

    print(best)


if __name__ == "__main__":
    main()
