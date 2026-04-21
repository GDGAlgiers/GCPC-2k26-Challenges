// Accepted solution — JavaScript (Node.js)
// Replace this with the actual correct solution.
const lines = require("fs")
  .readFileSync("/dev/stdin", "utf8")
  .trim()
  .split("\n");
let idx = 0;
const readline = () => lines[idx++];

// TODO: read input and solve
