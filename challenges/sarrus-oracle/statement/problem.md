---
title: "The Sarrus Oracle"
author: "tarek-ait"
difficulty: "Medium"
---


# The Sarrus Oracle

In the old academy of arithmetic, a broken oracle is still used to test if a
number is prime.

The theory behind it starts with Fermat's little theorem:

$$a^p \equiv a \pmod p$$

for every prime number $p$ and every integer $a$.

This oracle uses the particular choice $a = 2$, so it checks whether a number
satisfies the congruence

$$2^n \equiv 2 \pmod n.$$

The oracle incorrectly assumes the converse is also true: if a number satisfies

$$2^n \equiv 2 \pmod n,$$

then it must be prime. But this is false: some composite integers still
satisfy the same congruence.

In this problem, any composite integer with that property is called a
**Sarrus number**. The classic example is $341 = 11 \times 31$.

So there are three important facts to keep in mind:

- every prime number passes the test
- some composite numbers also pass the test
- only those composite false positives are counted in this problem

That last point matters: prime numbers satisfy the congruence too, but they
are **not** Sarrus numbers and must not be counted.

The academy stores candidate numbers in long consecutive archives. For each
interval $[L, R]$, determine how many integers in that interval would fool the
oracle - in other words, how many Sarrus numbers belong to that range.

**Task:** For each query $[L, R]$, count the composite integers $n$ such that
$L \le n \le R$ and $2^n \equiv 2 \pmod n$.

You may think of each query as one question asking:

> "Inside the interval $[L, R]$, how many composite numbers look prime to the
> oracle?"

## Input

The first line contains a single integer $q$ ($1 \leq q \leq 2 \cdot 10^5$) -
the number of queries.

Each of the next $q$ lines contains two integers $L$ and $R$
($2 \leq L \leq R \leq 2 \cdot 10^6$), describing one interval.

## Output

For each query, print a single integer: the number of Sarrus numbers in the
interval $[L, R]$.

## Constraints

- $1 \leq q \leq 2 \cdot 10^5$
- $2 \leq L \leq R \leq 2 \cdot 10^6$
- Time limit: **3 seconds**
- Memory limit: **512 MB**

## Sample Input 1

```text
4
2 100
300 400
500 700
1000 2000
```

## Sample Output 1

```text
0
1
2
4
```

## Explanation

- There are no Sarrus numbers between `2` and `100`.
- In `[300, 400]`, the only one is `341`.
- In `[500, 700]`, the two Sarrus numbers are `561` and `645`.
- In `[1000, 2000]`, they are `1105`, `1387`, `1729`, and `1905`.

Notice that prime numbers inside those intervals are ignored, even though they
also satisfy the oracle's congruence.
