"use strict";

const fs = require("fs");
const input = fs.readFileSync(0);
let offset = 0;

function nextInt() {
    let num = 0;
    while (offset < input.length && (input[offset] < 48 || input[offset] > 57)) offset++;
    if (offset >= input.length) return null;
    while (offset < input.length && input[offset] >= 48 && input[offset] <= 57) {
        num = num * 10 + (input[offset] - 48);
        offset++;
    }
    return num;
}

// Memory Pool for Treap
const MAX_NODES = 1000005; 
const valArr = new Float64Array(MAX_NODES); // Use Float64 to safely store up to 2^53
const priorityArr = new Float32Array(MAX_NODES);
const leftArr = new Int32Array(MAX_NODES);
const rightArr = new Int32Array(MAX_NODES);
let nodePtr = 1;

function newNode(v) {
    let id = nodePtr++;
    valArr[id] = v;
    priorityArr[id] = Math.random();
    return id;
}

function split(node, v) {
    if (node === 0) return [0, 0];
    if (valArr[node] <= v) {
        const [l, r] = split(rightArr[node], v);
        rightArr[node] = l;
        return [node, r];
    } else {
        const [l, r] = split(leftArr[node], v);
        leftArr[node] = r;
        return [l, node];
    }
}

// Corrected: Split to isolate exactly ONE node with value 'v'
function splitOne(node, v) {
    if (node === 0) return [0, 0, 0];
    if (valArr[node] < v) {
        const [l, m, r] = splitOne(rightArr[node], v);
        rightArr[node] = l;
        return [node, m, r];
    } else if (valArr[node] > v) {
        const [l, m, r] = splitOne(leftArr[node], v);
        leftArr[node] = r;
        return [l, m, node];
    } else {
        // Found the value, separate this specific node from its children
        let l = leftArr[node], r = rightArr[node];
        leftArr[node] = rightArr[node] = 0;
        return [l, node, r];
    }
}

function merge(l, r) {
    if (l === 0 || r === 0) return l || r;
    if (priorityArr[l] > priorityArr[r]) {
        rightArr[l] = merge(rightArr[l], r);
        return l;
    } else {
        leftArr[r] = merge(l, leftArr[r]);
        return r;
    }
}

/**
 * Re-implemented rev() using BigInt 
 * This prevents the 31st bit from causing negative signed-int issues
 */
function rev(x) {
    let bx = BigInt(x);
    for (let i = 0n; i < 16n; i++) {
        let bitI = (bx >> i) & 1n;
        let bitOpp = (bx >> (31n - i)) & 1n;
        
        if (bitI !== bitOpp) {
            bx ^= (1n << i);
            bx ^= (1n << (31n - i));
        }
    }
    return Number(bx);
}

function solve() {
    let Q = nextInt();
    if (Q === null) return;

    let root1 = 0, root2 = 0;
    let sum1 = 0n, sum2 = 0n;
    let count = 0;
    let bl = true;
    let results = [];

    while (Q--) {
        let typ = nextInt();
        if (typ === 1) {
            let x = nextInt();
            let x2 = rev(x);
            
            // Logic must strictly match C++ assignments
            if (bl) {
                let [l1, r1] = split(root1, x);
                root1 = merge(merge(l1, newNode(x)), r1);
                let [l2, r2] = split(root2, x2);
                root2 = merge(merge(l2, newNode(x2)), r2);
                sum1 += BigInt(x); sum2 += BigInt(x2);
            } else {
                let [l2, r2] = split(root2, x);
                root2 = merge(merge(l2, newNode(x)), r2);
                let [l1, r1] = split(root1, x2);
                root1 = merge(merge(l1, newNode(x2)), r1);
                sum2 += BigInt(x); sum1 += BigInt(x2);
            }
            count++;
        } else if (typ === 2) {
            let target = bl ? Number(sum1 / BigInt(count)) : Number(sum2 / BigInt(count));
            let curr = bl ? root1 : root2;
            let best = -1;

            // Equivalent to upper_bound(men)--
            while (curr !== 0) {
                if (valArr[curr] <= target) {
                    best = valArr[curr];
                    curr = rightArr[curr];
                } else {
                    curr = leftArr[curr];
                }
            }

            let bestRev = rev(best);
            
            // Remove exactly one instance of 'best' from primary and 'bestRev' from secondary
            let [l1, m1, r1] = splitOne(root1, bl ? best : bestRev);
            root1 = merge(l1, merge(splitOne(m1, bl ? best : bestRev)[0], r1));
            
            let [l2, m2, r2] = splitOne(root2, bl ? bestRev : best);
            root2 = merge(l2, merge(splitOne(m2, bl ? bestRev : best)[0], r2));

            sum1 -= BigInt(bl ? best : bestRev);
            sum2 -= BigInt(bl ? bestRev : best);
            results.push(best);
            count--;
        } else if (typ === 3) {
            bl = !bl;
        }
    }
    process.stdout.write(results.join("\n") + "\n");
}

solve();