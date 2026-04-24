---
title: "Hoggar Trail"
author: "Firas Mohamed Elamine Kiram"
difficulty: "Hard"
---


# Hoggar Trail

The Hoggar Mountains, located in southern Algeria near Tamanrasset, are among the most
famous mountainous regions in the country. A hiking club recorded the altitude of $n$
checkpoints along a long desert trail, where the $i$-th checkpoint has altitude $a_i$.

A hiker may choose any subsequence of these checkpoints, keeping their original order,
to form a personal route. The **effort** of a route is defined as the total altitude
change between consecutive chosen checkpoints. More formally, if the chosen route is
$s_1, s_2, \dots, s_k$, then its effort is:

$$\sum_{i=2}^{k} |s_i - s_{i-1}|$$

A route containing fewer than two checkpoints has effort $0$.

**Task:** Compute the total sum of efforts over all possible routes, modulo $10^9 + 7$.

## Input

The first line contains a single integer $n$ ($1 \leq n \leq 10^5$), the number of checkpoints.

The second line contains $n$ space-separated integers $a_1, a_2, \ldots, a_n$
($-10^9 \leq a_i \leq 10^9$), where $a_i$ is the altitude of the $i$-th checkpoint.

## Output

Print a single integer — the sum of efforts of all possible routes, modulo $10^9 + 7$.

## Constraints

- $1 \leq n \leq 10^5$
- $-10^9 \leq a_i \leq 10^9$
- Time limit: **2 seconds**
- Memory limit: **256 MB**

## Sample Input 1

3
2 7 5

## Sample Output 1

17

## Sample Input 2

1
5

## Sample Output 2

0

## Explanation

For the array `[2, 7, 5]`, we consider all subsequences with at least two elements and
sum their efforts:

- `[2, 7]` → $|7 - 2| = 5$
- `[2, 5]` → $|5 - 2| = 3$
- `[7, 5]` → $|5 - 7| = 2$
- `[2, 7, 5]` → $|7 - 2| + |5 - 7| = 5 + 2 = 7$

Total: $5 + 3 + 2 + 7 = 17$.

For a single checkpoint, no route with two or more elements exists, so the answer is $0$.