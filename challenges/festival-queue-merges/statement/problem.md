---
title: "Festival Queue Merges"
author: "Lyes Boudjabout"
difficulty: "Easy"
---

<!--
  RENDER PDF (run from inside the challenge directory, not statement/):
    ../../scripts/render-pdf.sh

  Requirements: pandoc + texlive-xetex
    sudo apt install pandoc texlive-xetex texlive-fonts-recommended texlive-latex-extra
-->

# Festival Queue Merges

A city festival has opened $K$ entry gates. Each gate has its own queue of visitors.
During the day, the organisers keep re-routing people between gates to balance traffic.

You are given $Q$ operations that modify queue sizes. After each `QUERY` operation,
you must report the busiest gate.

If multiple gates have the same maximum queue size, choose the **smallest gate index**.

**Task:** Process all operations and print the answer for every `QUERY`.

## Input

The first line contains two integers $K$ and $Q$ ($1 \le K, Q \le 2\cdot10^5$) -
the number of gates and the number of operations.

Each of the next $Q$ lines is one of the following operations:

- `ADD g x` : add $x$ people to gate $g$.
- `SERVE g x` : remove up to $x$ people from gate $g$.
  (Queue size cannot go below 0.)
- `MOVE a b x` : move up to $x$ people from gate $a$ to gate $b$.
- `MERGE a b` : append all people from gate $b$ to gate $a$, then gate $b$ becomes empty.
- `QUERY` : ask for the busiest gate.

All indices satisfy $1 \le g,a,b \le K$, and for `MOVE`/`MERGE`, $a \ne b$.
All amounts satisfy $1 \le x \le 10^9$.

## Output

For each `QUERY`, print one line with two integers:

- the gate index with the maximum current queue size,
- that queue size.

Break ties by choosing the smallest gate index.

## Constraints

- $1 \le K, Q \le 2\cdot10^5$
- $1 \le x \le 10^9$
- Time limit: **2 seconds**
- Memory limit: **256 MB**

## Sample Input 1

```
4 11
ADD 1 5
ADD 2 3
QUERY
MOVE 1 2 4
QUERY
SERVE 2 2
ADD 3 9
MERGE 2 3
QUERY
ADD 4 14
QUERY
```

## Sample Output 1

```
1 5
2 7
2 14
2 14
```

## Explanation

- After the first two operations: queues are `[5, 3, 0, 0]` -> `QUERY` gives `1 5`.
- `MOVE 1 2 4` makes queues `[1, 7, 0, 0]` -> `QUERY` gives `2 7`.
- `SERVE 2 2`, `ADD 3 9`, `MERGE 2 3` makes queues `[1, 14, 0, 0]` -> `QUERY` gives `2 14`.
- `ADD 4 14` makes `[1, 14, 0, 14]`; tie between gates 2 and 4, pick smaller index -> `2 14`.
