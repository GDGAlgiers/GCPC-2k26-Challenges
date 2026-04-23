"use strict";

const fs = require('fs');

function solve() {
    const input = fs.readFileSync(0);
    let offset = 0;

    function nextString() {
        while (offset < input.length && input[offset] <= 32) offset++;
        let start = offset;
        while (offset < input.length && input[offset] > 32) offset++;
        return input.slice(start, offset).toString();
    }

    function nextInt() { return parseInt(nextString()); }

    const n = nextInt();
    if (isNaN(n)) return;

    const p = [];
    for (let i = 0; i < n; i++) {
        p.push({ x: nextInt(), y: nextInt() });
    }
    p.push(p[0]);

    const N = 2005;
    const MOD = 998244353n;
    const OO = 2000000000000000000n;

    const inGrid = new Uint8Array(N * N);
    const addGrid = new Uint8Array(N * N);
    const window = new Int32Array(N);
    const dist = new BigInt64Array(N * N).fill(OO);

    for (let i = 1; i <= n; i++) {
        let { x, y } = p[i];
        let { x: px, y: py } = p[i - 1];

        for (let j = Math.min(py, y); j <= Math.max(py, y); j++) inGrid[x * N + j] = 1;
        for (let j = Math.min(px, x); j <= Math.max(px, x); j++) inGrid[j * N + y] = 1;
        for (let j = Math.min(py, y); j < Math.max(py, y); j++)  addGrid[x * N + j] = 1;
    }

    const sources = [];
    for (let x = 0; x < N; x++) {
        for (let y = 0; y < N; y++) {
            let idx = x * N + y;
            if (inGrid[idx]) sources.push(idx);
            inGrid[idx] |= (window[y] & 1);
            window[y] += addGrid[idx];
        }
    }

    let head = 0;
    const queue = new Int32Array(sources.length + N * N);
    for (let i = 0; i < sources.length; i++) {
        let idx = sources[i];
        dist[idx] = 0n;
        queue[i] = idx;
    }
    let tail = sources.length;

    const dx = [1, -1, 0, 0], dy = [0, 0, 1, -1];

    while (head < tail) {
        const idx = queue[head++];
        const x = Math.floor(idx / N);
        const y = idx % N;

        for (let k = 0; k < 4; k++) {
            const nx = x + dx[k], ny = y + dy[k];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                const nIdx = nx * N + ny;
                if (dist[nIdx] === OO && inGrid[nIdx]) {
                    dist[nIdx] = dist[idx] + 1n;
                    queue[tail++] = nIdx;
                }
            }
        }
    }

    let vals = [];
    for (let i = 0; i < N * N; i++) {
        if (inGrid[i]) vals.push(dist[i]);
    }
    vals.sort((a, b) => (a < b ? -1 : a > b ? 1 : 0));

    let ans = 0n, pw = 1n;
    for (let v of vals) {
        ans = (ans + (v % MOD) * pw) % MOD;
        pw = (pw * 2n) % MOD;
    }

    const power = (a, b) => {
        let res = 1n;
        a %= MOD;
        while (b > 0n) {
            if (b % 2n === 1n) res = (res * a) % MOD;
            a = (a * a) % MOD;
            b /= 2n;
        }
        return res;
    };

    const inv = power((pw - 1n + MOD) % MOD, MOD - 2n);
    console.log(((ans * inv) % MOD).toString());
}

solve();