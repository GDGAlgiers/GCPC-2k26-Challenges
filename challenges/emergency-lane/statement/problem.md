---
title: "Emergency Lane"
author: "tarek-ait"
difficulty: "Medium"
---

<!--
  RENDER PDF (run from inside the challenge directory, not statement/):
    ../../scripts/render-pdf.sh

  Requirements: pandoc + texlive-xetex
    sudo apt install pandoc texlive-xetex texlive-fonts-recommended texlive-latex-extra
-->

# Emergency Lane

A power surge hits the GCPC control network just before the final rehearsal.
Nadia must drive from the backup garage in city $1$ to the main broadcast hub
in city $n$ as fast as possible.

The city road map has $n$ intersections and $m$ bidirectional roads. Each road
has a positive travel time. To help emergency vehicles, the city grants Nadia
one **priority pass**: she may use it on **at most one road**, making the
travel time of that single road equal to `0`.

She may choose not to use the pass at all.

**Task:** Find the minimum possible time to travel from city $1$ to city $n$.
If city $n$ is unreachable, print `-1`.

## Input

The first line contains two integers $n$ and $m$:

- $n$ — the number of cities
- $m$ — the number of roads

Each of the next $m$ lines contains three integers $u$, $v$, and $w$,
describing a bidirectional road between cities $u$ and $v$ with travel time
$w$.

## Output

Print a single integer — the minimum possible travel time from city $1$ to city
$n$ using the priority pass on at most one road, or `-1` if no route exists.

## Sample Input 1

```text
5 6
1 2 4
2 5 9
1 3 2
3 4 2
4 5 2
2 4 3
```

## Sample Output 1

```text
4
```

## Sample Input 2

```text
4 2
1 2 5
3 4 1
```

## Sample Output 2

```text
-1
```

## Explanation

In the first sample, without using the pass, the best route is
`1 -> 3 -> 4 -> 5` with total cost `6`.

If Nadia uses the priority pass on the road `(4, 5)`, the same route costs

$$
2 + 2 + 0 = 4,
$$

which is optimal.

In the second sample, city `4` is disconnected from city `1`, so the answer is
`-1`.
