const fs = require('fs');

function sz(n, k) {
    if (k > n) return 0n;
    if (n === 1n) return 1n;
    return (n % 2n === 0n) ? 2n * sz(n / 2n, k) : 1n + 2n * sz(n / 2n, k);
}

function f(n, k) {
    if (k > n) return 0n;
    if (n === 1n) return 1n;
    if (n % 2n === 0n) return 2n * f(n / 2n, k) + (n / 2n) * sz(n / 2n, k);
    const m = (n + 1n) / 2n;
    return m + 2n * f(n / 2n, k) + m * sz(n / 2n, k);
}

const input = fs.readFileSync(0, 'utf-8').split(/\s+/);
if (input.length >= 4) {
    const r = f(BigInt(input[0]), BigInt(input[1]));
    const h = f(BigInt(input[2]), BigInt(input[3]));
    if (r > h) console.log("Raouf");
    else if (r < h) console.log("Hachem");
    else console.log("Tie");
}