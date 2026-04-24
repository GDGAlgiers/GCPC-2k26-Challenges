---
title: "Arduino Breadboard Setup"
author: "Raouf Ould Ali"
difficulty: "Medium"
---

You are finalizing a hardware project for the upcoming GDG Competitive Programming Contest (GCPC). You're working with a standard breadboard that consists of **N columns** and **M rows** of holes.

Because of how breadboards are built internally, all **M holes in the same column are electrically connected**. Furthermore, you have placed exactly one LED on each of the **N columns**.

You are given **Q jumper cables** to connect various parts of the board. For each query, you attempt to connect a cable between two specific holes: **($r_1$, $c_1$)** and **($r_2$, $c_2$)**. However, physical constraints apply:

1. A single hole can only fit one cable end. If you attempt to plug a cable into a hole that is already occupied by a previous cable, you cannot make the connection, and the cable is discarded.
2. When two columns are connected via a cable, they become part of the same electrical circuit. This means all LEDs in the same connected circuit must share the exact same state (either all ON, or all OFF).

After processing each cable, you need to calculate the **total number of different possible valid lighting configurations** for the **N LEDs**. Since this number can be very large, output it modulo **$10^9 + 7$**.

**Task:** For each of the Q queries, output the number of valid LED lighting configurations after processing that query, modulo $10^9 + 7$.

## Input

The first line contains three integers **N**, **M**, and **Q** — the number of columns, the number of rows (holes per column), and the number of cables.

The next **Q** lines each contain four integers **$r_1$**, **$c_1$**, **$r_2$**, and **$c_2$** (1 ≤ $r_1$, $r_2$ ≤ M, 1 ≤ $c_1$, $c_2$ ≤ N), representing an attempt to connect a cable between the hole at row **$r_1$** of column **$c_1$** and the hole at row **$r_2$** of column **$c_2$**.

## Output

Print **Q** lines. On the **i-th** line, print the total number of different valid LED lighting configurations after processing the **i-th** query, modulo **$10^9 + 7$**.

*Note: If the i-th query is invalid because one or both holes are already occupied, the configuration does not change, but you should still output the current answer.*

## Constraints

- $1 \leq N \leq 10^5$
- $1 \leq M \leq 5$
- $1 \leq Q \leq 10^5$
- Time limit: **1 second**
- Memory limit: **256 MB**

## Sample Input 1

```
3 2 4
1 1 1 2
2 1 1 2
2 2 1 3
2 1 2 3
```

## Sample Output 1

```
4
4
2
2
```

## Explanation

Initially, there are 8 possible configurations. 

1. After the first query, we connect column 1 and column 2. This results in $4$ configurations.

2. The second query attempts to connect column 1 and column 2 again, but since the holes are already occupied by the first cable, this query is invalid. The configuration remains the same with 4 valid configurations.

3. The third query connects column 2 and column 3. This results in 2 configurations.

4. The number remains the same with 2 valid configurations.