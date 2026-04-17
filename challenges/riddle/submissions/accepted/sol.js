const fs = require('fs');

function solve() {
    const input = fs.readFileSync(0, 'utf-8').trim().split(/\s+/);
    if (input.length < 2 || input[0] === "") return;
    const n = parseInt(input[0], 10);
    const d = parseInt(input[1], 10);
    
    const dp = new Float64Array((1 << n) * n);
    
    for (let i = 0; i < n; i++) {
        dp[(1 << i) * n + i] = 1;
    }
    
    const adj_mask = new Int32Array(n);
    for (let i = 0; i < n; i++) {
        for (let j = Math.max(i - d, 0); j < i; j++) {
            adj_mask[i] |= (1 << j);
        }
        for (let j = Math.min(i + d, n - 1); j > i; j--) {
            adj_mask[i] |= (1 << j);
        }
    }
    
    for (let mask = 1; mask < (1 << n); mask++) {
        const maskOffset = mask * n;
        for (let i = 0; i < n; i++) {
            const currentVal = dp[maskOffset + i];
            if (!(mask & (1 << i)) || currentVal === 0) continue;
            
            let cur = adj_mask[i] & (~mask);
            while (cur > 0) {
                let lowestBit = cur & -cur;
                let idx = 31 - Math.clz32(lowestBit); 
                
                const nextMaskOffset = (mask | (1 << idx)) * n;
                dp[nextMaskOffset + idx] = (dp[nextMaskOffset + idx] + currentVal);
                
                cur ^= lowestBit;
            }
        }
    }
    
    let ans = 0;
    const fullMaskOffset = ((1 << n) - 1) * n;
    for (let i = 0; i < n; i++) {
        ans = (ans + dp[fullMaskOffset + i]);
    }
    process.stdout.write(ans.toString() + '\n');
}

solve();