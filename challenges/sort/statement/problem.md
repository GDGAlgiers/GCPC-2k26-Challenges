---
title: "Rassim Sort"
author: "Redhouane Abdellah"
difficulty: "Medium"
---

# Rassim Sort

Rassim is bored out of his mind, he wants to play a game with his best friend Adnane; Adnane, being nice and wholesome, comes up with a fun challenge involving arrays.

The rules are simple, Rassim has an array $a$ of length $n$ and is given an integer $k$ by Adnane, he must find the number of indices $1 \le i \le n-k$ such that the subarray $[a_i, a_{i+1}, \cdots, a_{i+k}]$ with length $k+1$ (**not** with length $k$) satisfies the following property: $2^0 \cdot a_i < 2^1 \cdot a_{i+1} < 2^2 \cdot a_{i+2} < \cdots < 2^k \cdot a_{i+k}$.

If Rassim fails to complete the challenge before Adnane finished eating all of the pizza from the canteen, Adnane will bully his friends and destroy all of Wissal's stuffed animals, so he needs your help to find a fast algorithmic solution to this challenge.

**Task:** Determine the number of indices that satisfy the condition.


## Input

The first line of input contains two integers $n$ and $k$.

The second line of input contains $n$ integers $a_1, a_2,\cdots, a_n$.

## Output

Output a single integer, the number of indices satisfying the condition.

## Constraints

- $3 \le n \le 2 \cdot 10^5$
- $1 \le k < n$
- Time limit: **1.0 seconds**
- Memory limit: **256 MB**

## Sample Input 1

```
4 2
1 10 100 1000
```

## Sample Output 1

```
2
```

## Explanation

Both subarrays satisfy the condition:

- $i = 1$: the subarray $[a_1,a_2,a_3] = [1, 10, 100]$, and $2^0 \cdot 1 < 2^1 \cdot 10 < 2^2 \cdot 100$.

- $i = 2$: the subarray $[a_2,a_3,a_4] = [10,100,1000]$ and  $2^0 \cdot 10 < 2^1 \cdot 100 < 2^2 \cdot 1000$.

## Sample Input 2

```
9 3
3 9 12 3 9 12 3 9 12
```

## Sample Output 2

```
0
```