const tokens = require("fs").readFileSync(0, "utf8").trim().split(/\s+/);

if (tokens.length === 0 || tokens[0] === "") {
  process.exit(0);
}

let idx = 0;
const N = Number(tokens[idx++]);

const mat = Array.from({ length: N }, () => Array(N).fill(0));
for (let i = 0; i < N; i++) {
  for (let j = 0; j < N; j++) {
    mat[i][j] = Number(tokens[idx++]);
  }
}

let best = N;

for (let mask = 0; mask < (1 << N); mask++) {
  const covered = Array(N).fill(0);
  let count = 0;

  for (let i = 0; i < N; i++) {
    if (mask & (1 << i)) {
      count++;
      covered[i] = 1;

      for (let j = 0; j < N; j++) {
        if (mat[i][j] === 1) {
          covered[j] = 1;
        }
      }
    }
  }

  let ok = true;
  for (let i = 0; i < N; i++) {
    if (!covered[i]) {
      ok = false;
      break;
    }
  }

  if (ok && count < best) {
    best = count;
  }
}

process.stdout.write(String(best) + "\n");
