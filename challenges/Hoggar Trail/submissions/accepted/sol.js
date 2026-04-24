const fs = require('fs');

const M = 1000000007n;
const N = 100010;

function add(a, b) {
    return (a + b) % M;
}

function mul(a, b) {
    return (a * b) % M;
}

function sub(a, b) {
    return ((a - b) % M + M) % M;
}

const pw = new Array(N).fill(0n);

class Node {
    constructor(cnt = 0n, sum = 0n) {
        this.cnt = cnt;
        this.sum = sum;
    }
}

const neutral = new Node();

class SegTree {
    constructor(start, end) {
        this.start = start;
        this.end = end;
        this.node = new Node();
        this.left = null;
        this.right = null;
    }

    extend() {
        if (this.left === null) {
            let mid = Math.floor((this.start + this.end) / 2);
            this.left = new SegTree(this.start, mid);
            this.right = new SegTree(mid + 1, this.end);
        }
    }

    pushup(a, b) {
        return new Node(add(a.cnt, b.cnt), add(a.sum, b.sum));
    }

    update(idx, sum, cnt) {
        if (this.start > idx || this.end < idx) return;
        if (this.start === this.end) {
            this.node.cnt = add(this.node.cnt, cnt);
            this.node.sum = add(this.node.sum, sum);
            return;
        }
        this.extend();
        this.left.update(idx, sum, cnt);
        this.right.update(idx, sum, cnt);
        this.node = this.pushup(this.left.node, this.right.node);
    }

    query(l, r) {
        if (r < this.start || this.end < l) return neutral;
        if (l <= this.start && this.end <= r) return this.node;
        this.extend();
        return this.pushup(this.left.query(l, r), this.right.query(l, r));
    }
}

function solve() {
    // Read all input from standard input efficiently
    const input = fs.readFileSync(0, 'utf-8').trim().split(/\s+/);
    if (input.length === 0 || input[0] === '') return;

    let n = parseInt(input[0]);
    let a = new Array(n);
    let uniqueSet = new Set();

    for (let i = 0; i < n; i++) {
        a[i] = parseInt(input[i + 1]);
        uniqueSet.add(a[i]);
    }

    // Coordinate Compression
    let sortedUnique = Array.from(uniqueSet).sort((x, y) => x - y);
    let mp = new Map();
    let nxt = 1;
    for (let val of sortedUnique) {
        mp.set(val, nxt++);
    }

    let root = new SegTree(0, nxt + 5);
    let ans = 0n;

    for (let i = 0; i < n; i++) {
        let x = BigInt(a[i]);
        let mappedIdx = mp.get(a[i]);

        let left = root.query(0, mappedIdx - 1);
        let right = root.query(mappedIdx + 1, nxt + 5);

        let cur = sub(mul(left.cnt, x), left.sum);
        cur = add(cur, sub(right.sum, mul(right.cnt, x)));
        ans = add(ans, mul(cur, pw[n - i - 1]));
        root.update(mappedIdx, mul(x, pw[i]), pw[i]);
    }

    console.log(ans.toString());
}

function main() {
    pw[0] = 1n;
    for (let i = 1; i < N; i++) {
        pw[i] = (pw[i - 1] * 2n) % M;
    }
    
    let tc = 1;
    // For multiple test cases, you would read 'tc' from input[0] and offset accordingly
    while (tc--) {
        solve();
    }
}

main();