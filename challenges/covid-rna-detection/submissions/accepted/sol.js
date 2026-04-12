// Accepted solution — JavaScript (Node.js)
const lines = require("fs")
  .readFileSync("/dev/stdin", "utf8")
  .trim()
  .split("\n");
let idx = 0;
const readline = () => lines[idx++];

const rna = readline();
const markers = ["ACGUAUGC", "AUGCGUAG", "UGCUAGCU"];
for (const m of markers) {
  if (rna.includes(m)) {
    console.log("True");
    process.exit(0);
  }
}
console.log("False");
