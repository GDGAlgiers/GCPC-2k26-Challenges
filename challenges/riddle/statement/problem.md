---
title: "Permutation Riddle"
author: "Redhouane Abdellah"
difficulty: "Medium"
---

<!--
  RENDER PDF (run from inside the challenge directory, not statement/):
    ../../scripts/render-pdf.sh

  Requirements: pandoc + texlive-xetex
    sudo apt install pandoc texlive-xetex texlive-fonts-recommended texlive-latex-extra
-->

# Permutation Riddle

Ramzy is tired of waiting for the student allowance and has started looking for a way to earn some money; luckily, he stumbled upon a strange man named "The Permutation Prince" who challenged him to a "Permutation Riddle".

*"Find the number of permutations[^1] of size $n$ where neighbors differ by no more than $d$. Solve this count, and you shall claim a fortune equal to the lexicographically largest arrangement of six!"*

[^1]: A permutation of size $n$ is an arrangement of the integers from 1 to $n$ where each number appears exactly once.

Intrigued by the interesting challenge, and the large prize of 654,321 DA, Ramzy needs your help to solve this problem.

**Task:** Find the number of permutations of size $n$ where each pair of adjacent elements has an absolute difference of at most $d$.

## Input

The first and only line of input contains two integers $n$ and $d$.

## Output

Print a single integer — the number of permutations of size $n$ whose adjacent elements differ by at most $d$.

## Constraints

- $1 \le n \le 19$
- $1 \le d \le 5$
- Time limit: **2.0 seconds**
- Memory limit: **256 MB**

## Sample Input 1

```
4 2
```

## Sample Output 1

```
12
```

## Explanation

There are $12$ permutations of size $4$ whose adjacent elements differ by no more than $2$. 

The permutation $[1, 2, 4, 3]$ is valid because:

- $|2 - 1| = 1 \le 2$
- $|4 - 2| = 2 \le 2$
- $|3 - 4| = 1 \le 2$

However, the permutation $[1, 4, 2, 3]$ is **not** valid, since $|4 - 1| = 3$, which is greater than $d=2$.

## Sample Input 2

```
3 2
```

## Sample Output 2

```
6
```