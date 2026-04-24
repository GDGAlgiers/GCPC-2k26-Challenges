const fs = require("fs");
const tokens = fs.readFileSync(0, "utf8").trim().split(/\s+/);
if (tokens.length === 1 && tokens[0] === "") process.exit(0);

let p = 0;
const K = Number(tokens[p++]);
const Q = Number(tokens[p++]);

const cnt = Array(K + 1).fill(0);

class MaxHeap {
  constructor() {
    this.h = [];
  }

  better(a, b) {
    if (a[0] !== b[0]) return a[0] > b[0];
    return a[1] > b[1];
  }

  push(node) {
    const h = this.h;
    h.push(node);
    let i = h.length - 1;
    while (i > 0) {
      const par = (i - 1) >> 1;
      if (!this.better(h[i], h[par])) break;
      [h[i], h[par]] = [h[par], h[i]];
      i = par;
    }
  }

  pop() {
    const h = this.h;
    const ret = h[0];
    const last = h.pop();
    if (h.length > 0) {
      h[0] = last;
      let i = 0;
      while (true) {
        let best = i;
        const l = i * 2 + 1;
        const r = l + 1;
        if (l < h.length && this.better(h[l], h[best])) best = l;
        if (r < h.length && this.better(h[r], h[best])) best = r;
        if (best === i) break;
        [h[i], h[best]] = [h[best], h[i]];
        i = best;
      }
    }
    return ret;
  }

  top() {
    return this.h[0];
  }
}

const heap = new MaxHeap();
for (let i = 1; i <= K; i++) heap.push([0, -i]);

const out = [];

for (let it = 0; it < Q; it++) {
  const op = tokens[p++];

  if (op === "ADD") {
    const g = Number(tokens[p++]);
    const x = Number(tokens[p++]);
    cnt[g] += x;
    heap.push([cnt[g], -g]);
  } else if (op === "SERVE") {
    const g = Number(tokens[p++]);
    const x = Number(tokens[p++]);
    const t = Math.min(cnt[g], x);
    cnt[g] -= t;
    heap.push([cnt[g], -g]);
  } else if (op === "MOVE") {
    const a = Number(tokens[p++]);
    const b = Number(tokens[p++]);
    const x = Number(tokens[p++]);
    const t = Math.min(cnt[a], x);
    cnt[a] -= t;
    cnt[b] += t;
    heap.push([cnt[a], -a]);
    heap.push([cnt[b], -b]);
  } else if (op === "MERGE") {
    const a = Number(tokens[p++]);
    const b = Number(tokens[p++]);
    cnt[a] += cnt[b];
    cnt[b] = 0;
    heap.push([cnt[a], -a]);
    heap.push([cnt[b], -b]);
  } else {
    while (true) {
      const [c, negIdx] = heap.top();
      const idx = -negIdx;
      if (c === cnt[idx]) {
        out.push(`${idx} ${c}`);
        break;
      }
      heap.pop();
    }
  }
}

if (out.length > 0) process.stdout.write(out.join("\n") + "\n");
