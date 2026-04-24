// Accepted solution — JavaScript (Node.js)
const lines = require("fs")
  .readFileSync("/dev/stdin", "utf8")
  .trim()
  .split("\n");
let idx = 0;
const readline = () => lines[idx++];

// Helper to iterate through whitespace-separated tokens
let tokens = [];
let tokenIdx = 0;
function nextToken() {
  while (tokenIdx >= tokens.length) {
    let line = readline();
    if (line === undefined) return null;
    tokens = line.trim().split(/\s+/);
    tokenIdx = 0;
    // Handle empty lines correctly
    if (tokens.length === 1 && tokens[0] === "") tokens = [];
  }
  return tokens[tokenIdx++];
}

function solve() {
  let nStr = nextToken();
  let qStr = nextToken();
  if (!nStr || !qStr) return;
  
  let n = parseInt(nStr, 10);
  let Q = parseInt(qStr, 10);

  // We need up to log2(100000) ~ 16, 18 is safe.
  let maxLog = Math.floor(Math.log2(n)) + 2;
  
  // Flattening 2D arrays into 1D TypedArrays for performance & memory efficiency
  let st_c = new BigInt64Array(maxLog * (n + 1));
  let st_q = new Int8Array(maxLog * (n + 1));

  // Read input and initialize the base of the sparse table
  for (let i = 1; i <= n; i++) {
    let a = BigInt(nextToken());
    st_c[i] = a / 2n;
    st_q[i] = Number(a % 2n);
  }

  // Build the Sparse Table
  for (let p = 1; (1 << p) <= n; p++) {
    let prevRow = (p - 1) * (n + 1);
    let currRow = p * (n + 1);
    
    for (let i = 1; i + (1 << p) - 1 <= n; i++) {
      let idx1 = prevRow + i;
      let idx2 = prevRow + i + (1 << (p - 1));
      
      let c1 = st_c[idx1], q1 = st_q[idx1];
      let c2 = st_c[idx2], q2 = st_q[idx2];
      
      let target = currRow + i;
      if (c1 > c2) {
        st_c[target] = c1;
        st_q[target] = q1;
      } else if (c1 < c2) {
        st_c[target] = c2;
        st_q[target] = q2;
      } else {
        st_c[target] = c1;
        st_q[target] = (q1 === q2) ? q1 : 2;
      }
    }
  }

  // Process queries
  let out = [];
  for (let q = 0; q < Q; q++) {
    let k = parseInt(nextToken(), 10);
    let r = parseInt(nextToken(), 10);

    let L = k;
    let R = k + r - 1;

    // Using O(1) Sparse Table range query
    let p = Math.floor(Math.log2(R - L + 1));
    let row = p * (n + 1);
    
    let idx1 = row + L;
    let idx2 = row + R - (1 << p) + 1;
    
    let c1 = st_c[idx1], q1 = st_q[idx1];
    let c2 = st_c[idx2], q2 = st_q[idx2];
    
    let res_c, res_q;
    if (c1 > c2) {
      res_c = c1; res_q = q1;
    } else if (c1 < c2) {
      res_c = c2; res_q = q2;
    } else {
      res_c = c1;
      res_q = (q1 === q2) ? q1 : 2;
    }

    let base_val = res_c * 2n;

    if (res_q === 0) {
      out.push(base_val.toString());
    } else if (res_q === 1) {
      out.push((base_val + 1n).toString());
    } else {
      // Superposition outputs both possibilities in increasing order
      out.push(base_val.toString() + " " + (base_val + 1n).toString());
    }

    // Flush output buffer periodically to prevent memory errors with huge `Q`
    if (out.length >= 10000) {
      process.stdout.write(out.join('\n') + '\n');
      out = [];
    }
  }
  
  // Print any remaining output
  if (out.length > 0) {
    process.stdout.write(out.join('\n') + '\n');
  }
}

solve();
