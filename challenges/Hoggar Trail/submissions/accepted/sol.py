import sys

sys.setrecursionlimit(300000)

M = 10**9 + 7
N = 100010

def add(a, b):
    return (a + b) % M

def mul(a, b):
    return (a * b) % M

def sub(a, b):
    return ((a - b) % M + M) % M

pw = [0] * N
pw[0] = 1
for i in range(1, N):
    pw[i] = (pw[i - 1] * 2) % M

class Node:
    def __init__(self, cnt=0, sum=0):
        self.cnt = cnt
        self.sum = sum

neutral = Node(0, 0)

class SegTree:
    def __init__(self, start, end):
        self.start = start
        self.end = end
        self.node = Node(0, 0)
        self.left = None
        self.right = None

    def extend(self):
        if self.left is None:
            mid = (self.start + self.end) // 2
            self.left = SegTree(self.start, mid)
            self.right = SegTree(mid + 1, self.end)

    def pushup(self, a, b):
        return Node(add(a.cnt, b.cnt), add(a.sum, b.sum))

    def update(self, idx, sum_val, cnt_val):
        if self.start > idx or self.end < idx:
            return
        if self.start == self.end:
            self.node.cnt = add(self.node.cnt, cnt_val)
            self.node.sum = add(self.node.sum, sum_val)
            return
        
        self.extend()
        self.left.update(idx, sum_val, cnt_val)
        self.right.update(idx, sum_val, cnt_val)
        self.node = self.pushup(self.left.node, self.right.node)

    def query(self, l, r):
        if r < self.start or self.end < l:
            return neutral
        if l <= self.start and self.end <= r:
            return self.node
        
        self.extend()
        return self.pushup(self.left.query(l, r), self.right.query(l, r))

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    n = int(input_data[0])
    a = [int(x) for x in input_data[1:n+1]]
    
    unique_sorted = sorted(list(set(a)))
    
    mp = {val: idx + 1 for idx, val in enumerate(unique_sorted)}
    nxt = len(unique_sorted) + 1
    
    root = SegTree(0, nxt + 5)
    ans = 0
    
    for i in range(n):
        x = a[i]
        mapped_idx = mp[x]
        
        left_res = root.query(0, mapped_idx - 1)
        right_res = root.query(mapped_idx + 1, nxt + 5)
        
        cur = sub(mul(left_res.cnt, x), left_res.sum)
        cur = add(cur, sub(right_res.sum, mul(right_res.cnt, x)))
        
        ans = add(ans, mul(cur, pw[n - i - 1]))
        root.update(mapped_idx, mul(x, pw[i]), pw[i])
        
    print(ans)

if __name__ == '__main__':

    tc = 1
    for _ in range(tc):
        solve()