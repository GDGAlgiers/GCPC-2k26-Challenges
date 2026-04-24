// Accepted solution — JavaScript (Node.js)
const lines = require("fs")
  .readFileSync("/dev/stdin", "utf8")
  .trim()
  .split("\n");
let idx = 0;
const readline = () => lines[idx++];

const [N, B] = readline().split(" ").map(Number);

let dp = new Array(B + 1).fill(0n);
dp[0] = 1n;

for (let i = 0; i < N; i++) {
  const line = readline().split(" ").map(Number);
  const k = line[0];
  const replicas = line.slice(1);

  const ndp = new Array(B + 1).fill(0n);
  for (const latency of replicas)
    for (let b = latency; b <= B; b++) ndp[b] += dp[b - latency];
  dp = ndp;
}

console.log(dp.reduce((a, v) => a + v, 0n).toString());
