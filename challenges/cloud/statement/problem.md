---
title: "Cloud Battle"
author: "Redhouane Abdellah"
difficulty: "Medium"
---

# Cloud Battle

Raouf is on a national mission to the capital of Uzbekistan, Tashkent. During his journey, he gets bored and starts watching $n$ clouds aligned in the sky, numbered from $1$ to $n$. To pass the time, he begins a game involving a "cloudy score" based on the segments of clouds he observes. 

He uses a recursive procedure to look for the cloud in the middle of each segment $[l, r]$, but his responsibility score $k$ prevents him from observing any segment with a length strictly less than $k$. Not wanting to play alone, he challenges Hachem, who follows the same rules with $N$ clouds and a responsibility score $K$.

**Task:** Determine the winner of the game based on who achieves the higher cloudy score, or determine if the game ends in a tie.

## Rules of the Game

For a segment $[l, r]$ with length $len = r - l + 1$:

* If $len < k$, the observation stops for that segment.

* Calculate the middle index $m = \lfloor \frac{l+r}{2} \rfloor$.

* If the length of the segment is **even**, the segment is divided into two segments of the same length, $[l, m]$ and $[m+1, r]$, for further observation. No points are added to the score.

* If the length of the segment is **odd**, the cloudy score increases by $m$. If $l \neq r$, the observation continues with the two segments $[l, m-1]$ and $[m+1, r]$.

* He starts with the segment $[1,n]$ and continues to observe segments adhering to the other rules.

## Input

The first line of input contains two integers $n$ and $k$ ($1 \le k \le n \le 2 \cdot 10^9$), representing the number of clouds Raouf sees and his responsibility score, respectively.

The second line of input contains two integers $N$ and $K$ ($1 \le K \le N \le 2 \cdot 10^9$), representing the number of clouds Hachem sees and his responsibility score, respectively.

## Output

If Raouf has a bigger cloudy score than Hachem, print "Raouf".

If Hachem has a bigger cloudy score than Raouf, print "Hachem".

Otherwise, print "Tie".

## Constraints

- $1 \le k \le n \le 2 \cdot 10^9$
- $1 \le K \le N \le 2 \cdot 10^9$
- Time limit: **1.0 seconds**
- Memory limit: **256 MB**

## Sample Input 1

```
5 1
5 2
```

## Sample Output 1

```
Raouf
```

## Explanation

For Raouf ($n=5, k=1$):

* Segment $[1, 5]$ has odd length ($5$). $m = 3$. Score becomes $3$.

* Next segments are $[1, 2]$ and $[4, 5]$. Both have even length ($2$), so they split without adding score.

* Since $k=1$, Raouf processes the resulting segments $[1, 1], [2, 2], [4, 4], [5, 5]$, adding $1+2+4+5=12$ to the score.

* **Total score for Raouf:** $3 + 12 = 15$.

For Hachem ($N=5, K=2$):

* Segment $[1, 5]$ has odd length ($5$). $m=3$. Score becomes $3$.

* Next segments $[1, 2]$ and $[4, 5]$ have length $2$. Since $K=2$, they are processed (even length, no score) and split into segments of length $1$.

* However, segments of length $1$ are not observed because $1 < K$.

* **Total score for Hachem:** $3$.

Since $15 > 3$, Raouf wins.

## Sample Input 2

```
3 2
3 3
```

## Sample Output 2

```
Tie
```