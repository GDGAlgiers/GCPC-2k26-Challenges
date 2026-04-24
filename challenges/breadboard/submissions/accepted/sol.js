// Accepted solution — JavaScript (Node.js)
const lines = require("fs")
  .readFileSync("/dev/stdin", "utf8")
  .trim()
  .split("\n");
let idx = 0;
const readline = () => lines[idx++];

// Helper to read space-separated integers safely across lines
let currentTokens = [];
let currentTokenIdx = 0;

function nextInt() {
    while (currentTokenIdx >= currentTokens.length) {
        const line = readline();
        if (line === undefined) return null;
        currentTokens = line.trim().split(/\s+/);
        currentTokenIdx = 0;
        if (currentTokens[0] === '') currentTokens = [];
    }
    return parseInt(currentTokens[currentTokenIdx++], 10);
}

function main() {
    let N = nextInt();
    if (N === null) return; // EOF
    let M = nextInt();
    let Q = nextInt();

    const MOD = 1000000007;
    
    // Precompute powers of 2 for O(1) configuration calculation
    const power2 = new Int32Array(Math.max(100005, N + 1));
    power2[0] = 1;
    for (let i = 1; i <= N; i++) {
        power2[i] = (power2[i - 1] * 2) % MOD;
    }

    // DSU Initialization
    const parent = new Int32Array(N + 1);
    for (let i = 1; i <= N; i++) {
        parent[i] = i;
    }
    let components = N;

    function find(i) {
        if (parent[i] === i) return i;
        return parent[i] = find(parent[i]); // Path compression
    }

    function unite(i, j) {
        let root_i = find(i);
        let root_j = find(j);
        if (root_i !== root_j) {
            parent[root_i] = root_j;
            components--;
        }
    }

    // Track occupied holes using a Set of strings "r_c"
    const occupied = new Set();
    const getKey = (r, c) => `${r}_${c}`;
    
    // Buffer output to prevent slow I/O operations
    const out = [];

    for (let i = 0; i < Q; i++) {
        let r1 = nextInt();
        let c1 = nextInt();
        let r2 = nextInt();
        let c2 = nextInt();

        let key1 = getKey(r1, c1);
        let key2 = getKey(r2, c2);

        // Check if either hole is already occupied
        if (occupied.has(key1) || occupied.has(key2)) {
            // Discard cable, record current configuration
            out.push(power2[components]);
        } else {
            // Mark holes as occupied and connect columns
            occupied.add(key1);
            occupied.add(key2);
            unite(c1, c2);
            out.push(power2[components]);
        }
    }

    // Print all outputs at once
    console.log(out.join("\n"));
}

main();