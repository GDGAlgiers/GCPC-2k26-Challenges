// Accepted solution — JavaScript (Node.js)
const lines = require("fs")
  .readFileSync("/dev/stdin", "utf8")
  .trim()
  .split("\n");
let idx = 0;
const readline = () => lines[idx++];

const [N, W, X, C] = readline().split(" ").map(Number);
const E = parseInt(readline());

const failures = Array.from({ length: N }, () => []);

for (let i = 0; i < E; i++) {
  const [T, S, R] = readline().split(" ").map(Number);
  if (R === 0) failures[S].push(T);
}

const intervals = Array.from({ length: N }, () => []);

for (let s = 0; s < N; s++) {
  const fl = failures[s];
  let skipUntil = -1;
  let valid = [];

  for (const t of fl) {
    if (t < skipUntil) continue;
    valid.push(t);
    while (valid.length > 0 && valid[0] < t - W) valid.shift();
    if (valid.length === X) {
      const openTime = t;
      const closeTime = openTime + C;
      intervals[s].push([openTime, closeTime]);
      skipUntil = closeTime;
      valid = [];
    }
  }
}

const Q = parseInt(readline());
const out = [];

for (let i = 0; i < Q; i++) {
  const [T, S] = readline().split(" ").map(Number);
  const ivs = intervals[S];
  let lo = 0,
    hi = ivs.length - 1;
  let found = false;
  while (lo <= hi) {
    const mid = (lo + hi) >> 1;
    if (ivs[mid][0] <= T) {
      if (ivs[mid][1] > T) {
        found = true;
        break;
      }
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  out.push(found ? "OPEN" : "CLOSED");
}

console.log(out.join("\n"));
