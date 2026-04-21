const fs = require("fs");

const input = fs.readFileSync(0, "utf8").trim();
if (input.length === 0) {
  process.exit(0);
}

const data = input.split(/\s+/).map(Number);
let idx = 0;

const n = data[idx++];
const m = data[idx++];

const graph = Array.from({ length: n + 1 }, () => []);
const roads = [];

for (let i = 0; i < m; i++) {
  const u = data[idx++];
  const v = data[idx++];
  const w = data[idx++];
  graph[u].push([v, w]);
  graph[v].push([u, w]);
  roads.push([u, v]);
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

const distStart = dijkstra(1);
const distEnd = dijkstra(n);

let ans = distStart[n];
for (const [u, v] of roads) {
  if (distStart[u] < INF / 2 && distEnd[v] < INF / 2) {
    ans = Math.min(ans, distStart[u] + distEnd[v]);
  }
  if (distStart[v] < INF / 2 && distEnd[u] < INF / 2) {
    ans = Math.min(ans, distStart[v] + distEnd[u]);
  }
}

console.log(ans >= INF / 2 ? -1 : Math.trunc(ans));
