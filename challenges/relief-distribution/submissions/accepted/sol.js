const fs = require("fs");
const data = fs.readFileSync(0, "utf8").trim();

if (data.length === 0) {
  process.exit(0);
}

const arr = data.split(/\s+/).map(Number);
let p = 0;
const n = arr[p++];

const boxes = new Array(n);
for (let i = 0; i < n; i++) {
  const w = arr[p++];
  const d = arr[p++];
  boxes[i] = [d, w];
}

boxes.sort((a, b) => (a[0] - b[0]) || (a[1] - b[1]));

class MaxHeap {
  constructor() {
    this.h = [];
  }

  size() {
    return this.h.length;
  }

  push(x) {
    const h = this.h;
    h.push(x);
    let i = h.length - 1;
    while (i > 0) {
      const p = (i - 1) >> 1;
      if (h[p] >= h[i]) break;
      [h[p], h[i]] = [h[i], h[p]];
      i = p;
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
        let m = i;
        const l = i * 2 + 1;
        const r = l + 1;
        if (l < h.length && h[l] > h[m]) m = l;
        if (r < h.length && h[r] > h[m]) m = r;
        if (m === i) break;
        [h[i], h[m]] = [h[m], h[i]];
        i = m;
      }
    }
    return ret;
  }
}

const heap = new MaxHeap();
let total = 0;

for (const [d, w] of boxes) {
  heap.push(w);
  total += w;
  if (heap.size() > d) {
    total -= heap.pop();
  }
}

process.stdout.write(`${heap.size()} ${total}\n`);
