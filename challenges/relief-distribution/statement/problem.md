---
title: "Relief Distribution"
author: "Lyes Boudjabout"
difficulty: "Easy"
---


# Relief Distribution

After a natural disaster, a relief organisation has prepared emergency supply boxes for affected families. Each box has a limited shelf life and must be delivered before its expiry date, otherwise it spoils and becomes useless. With only one truck available and the ability to deliver exactly one box per day, the team must carefully decide which boxes to prioritise. They want to help as many families as possible, but among equally helpful schedules they prefer to minimise the total weight carried to save fuel and effort.

**Task:** Given the weight and expiry deadline of each box, determine the maximum number of boxes that can be delivered on time, and the minimum total weight required to achieve that maximum.

## Input

The first line contains a single integer $N$ ($1 \le N \le 10^5$) — the number of boxes.

The next $N$ lines each contain two integers $w_i$ and $d_i$ ($1 \le w_i \le 10^4$, $1 \le d_i \le N$) — the weight and expiry deadline of box $i$. A box with deadline $d_i$ must be delivered on or before day $d_i$.

## Output

Print two integers on a single line: the **maximum number of boxes** that can be delivered, followed by the **minimum total weight** achievable while delivering that many boxes.

## Constraints

- $1 \le N \le 10^5$
- $1 \le w_i \le 10^4$
- $1 \le d_i \le N$
- Time limit: **2 seconds**
- Memory limit: **256 MB**

## Sample Input 1

```
5
3 2
7 1
4 3
5 4
2 1
```

## Sample Output 1

```
4 14
```

## Explanation
The five boxes are:

| Box | Weight | Deadline |
|-----|--------|----------|
| 1   | 3      | 2        |
| 2   | 7      | 1        |
| 3   | 4      | 3        |
| 4   | 5      | 4        |
| 5   | 2      | 1        |

To maximise the number of deliveries (4 boxes) while minimising total weight, we schedule:

- **Day 1:** Box 5 (weight 2, deadline 1)
- **Day 2:** Box 1 (weight 3, deadline 2)
- **Day 3:** Box 3 (weight 4, deadline 3)
- **Day 4:** Box 4 (weight 5, deadline 4)

Box 2 (weight 7, deadline 1) is skipped — using it would force us to drop a lighter box on day 1, increasing the total weight without gaining an extra delivery. Any other schedule that also delivers four boxes will have a total weight of at least 14. Hence the answer is `4 14`.
