// Reference solution for "The Sarrus Oracle".
//
// Theory:
// - Every prime p satisfies 2^p == 2 (mod p).
// - Some composite numbers satisfy that too.
// - Only those composite false positives are counted.
//
// Strategy:
// 1. Read all queries and find the largest R.
// 2. Sieve all primes up to that limit.
// 3. For each composite n, test whether 2^n mod n == 2.
// 4. Build prefix sums and answer each interval in O(1).

const fs = require("fs");

const tokens = fs.readFileSync(0, "utf8").trim().split(/\s+/);
if (tokens.length === 0 || tokens[0] === "") {
  process.exit(0);
}

function modPow(base, exp, mod) {
  // Binary exponentiation under a modulus.
  let result = 1 % mod;
  let cur = base % mod;
  while (exp > 0) {
    if (exp & 1) {
      result = (result * cur) % mod;
    }
    cur = (cur * cur) % mod;
    exp >>= 1;
  }
  return result;
}

const q = Number(tokens[0]);
const queries = new Array(q);
let maxR = 0;
let idx = 1;

// Read all interval questions first so we know how far to preprocess.
for (let i = 0; i < q; i++) {
  const left = Number(tokens[idx++]);
  const right = Number(tokens[idx++]);
  queries[i] = [left, right];
  if (right > maxR) {
    maxR = right;
  }
}

// Sieve of Eratosthenes.
const prime = new Uint8Array(maxR + 1);
for (let i = 2; i <= maxR; i++) {
  prime[i] = 1;
}
for (let i = 2; i * i <= maxR; i++) {
  if (prime[i]) {
    for (let j = i * i; j <= maxR; j += i) {
      prime[j] = 0;
    }
  }
}

// prefix[n] = number of Sarrus numbers in [2, n].
const prefix = new Int32Array(maxR + 1);
let count = 0;
for (let n = 2; n <= maxR; n++) {
  // Prime numbers satisfy the congruence too, but they do not count.
  if (!prime[n] && modPow(2, n, n) === 2) {
    count++;
  }
  prefix[n] = count;
}

const out = new Array(q);
for (let i = 0; i < q; i++) {
  const [left, right] = queries[i];
  // Interval answer from prefix sums.
  out[i] = String(prefix[right] - prefix[left - 1]);
}

process.stdout.write(out.join("\n") + "\n");
