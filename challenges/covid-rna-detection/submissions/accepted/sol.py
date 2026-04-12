# Accepted solution — Python 3
import sys

input = sys.stdin.readline

MARKERS = ["ACGUAUGC", "AUGCGUAG", "UGCUAGCU"]


def main():
    rna = input().strip()
    for m in MARKERS:
        if m in rna:
            print("True")
            return
    print("False")


main()
