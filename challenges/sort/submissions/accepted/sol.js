const readline = require('readline');

const rl = readline.createInterface({ input: process.stdin });
const lines = [];

rl.on('line', line => lines.push(line.trim()));
rl.on('close', () => {
    const [n, k] = lines[0].split(' ').map(Number);
    const a = lines[1].split(' ').map(Number);

    const vec = [1];
    let ans = 0;

    for (let i = 1; i < n; i++) {
        if (a[i] * 2 > a[i - 1]) {
            vec[vec.length - 1]++;
        } else {
            vec.push(1);
        }
    }

    for (const x of vec) {
        ans += Math.max(x - k, 0);
    }

    console.log(ans);
});
