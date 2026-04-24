const fs = require("fs");

const input = fs.readFileSync(0, "utf8").trim();
if (input.length === 0) {
  process.exit(0);
}

const data = input.split(/\s+/).map(Number);
let idx = 0;

const n = data[idx++];
const m = data[idx++];
const k = data[idx++];

const relays = [];
for (let i = 0; i < k; i++) {
  relays.push(data[idx++]);
}

const graph = Array.from({ length: n + 1 }, () => []);
for (let i = 0; i < m; i++) {
  const u = data[idx++];
  const v = data[idx++];
  const w = data[idx++];
  graph[u].push([v, w]);
  graph[v].push([u, w]);
}

const INF = 1e30;

class MinHeap {
  constructor() {
    this.arr = [];
  }

  push(item) {
    this.arr.push(item);
    let i = this.arr.length - 1;
    while (i > 0) {
      const p = (i - 1) >> 1;
      if (this.arr[p][0] <= this.arr[i][0]) {
        break;
      }
      [this.arr[p], this.arr[i]] = [this.arr[i], this.arr[p]];
      i = p;
    }
  }

  pop() {
    const root = this.arr[0];
    const last = this.arr.pop();
    if (this.arr.length > 0) {
      this.arr[0] = last;
      let i = 0;
      while (true) {
        let smallest = i;
        const left = i * 2 + 1;
        const right = left + 1;
        if (left < this.arr.length && this.arr[left][0] < this.arr[smallest][0]) {
          smallest = left;
        }
        if (right < this.arr.length && this.arr[right][0] < this.arr[smallest][0]) {
          smallest = right;
        }
        if (smallest === i) {
          break;
        }
        [this.arr[i], this.arr[smallest]] = [this.arr[smallest], this.arr[i]];
        i = smallest;
      }
    }
    return root;
  }

  get size() {
    return this.arr.length;
  }
}

function dijkstra(src) {
  const dist = Array(n + 1).fill(INF);
  dist[src] = 0;
  const pq = new MinHeap();
  pq.push([0, src]);

  while (pq.size > 0) {
    const [d, u] = pq.pop();
    if (d !== dist[u]) {
      continue;
    }
    for (const [v, w] of graph[u]) {
      const nd = d + w;
      if (nd < dist[v]) {
        dist[v] = nd;
        pq.push([nd, v]);
      }
    }
  }

  return dist;
}

const important = [1, ...relays, n];
const count = important.length;
const distImp = Array.from({ length: count }, () => Array(count).fill(INF));

for (let i = 0; i < count; i++) {
  const dist = dijkstra(important[i]);
  for (let j = 0; j < count; j++) {
    distImp[i][j] = dist[important[j]];
  }
}

if (k === 0) {
  const ans = distImp[0][1];
  console.log(ans >= INF / 2 ? -1 : Math.trunc(ans));
  process.exit(0);
}

const size = 1 << k;
const dp = Array.from({ length: size }, () => Array(k).fill(INF));
for (let i = 0; i < k; i++) {
  dp[1 << i][i] = distImp[0][i + 1];
}

for (let mask = 0; mask < size; mask++) {
  for (let i = 0; i < k; i++) {
    const cur = dp[mask][i];
    if (cur >= INF / 2) {
      continue;
    }
    for (let j = 0; j < k; j++) {
      if (mask & (1 << j)) {
        continue;
      }
      const nextMask = mask | (1 << j);
      const nd = cur + distImp[i + 1][j + 1];
      if (nd < dp[nextMask][j]) {
        dp[nextMask][j] = nd;
      }
    }
  }
}

let ans = INF;
const full = size - 1;
for (let i = 0; i < k; i++) {
  ans = Math.min(ans, dp[full][i] + distImp[i + 1][k + 1]);
}

console.log(ans >= INF / 2 ? -1 : Math.trunc(ans));
