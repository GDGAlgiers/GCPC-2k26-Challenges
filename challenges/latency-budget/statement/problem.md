---
title: "Latency Budget"
author: "Bouzara Zakaria"
difficulty: "Easy"
---

# Latency Budget

A user clicks a button. What they do not see is their request silently
threading through a chain of microservices: authentication, business logic,
database, cache. Each service runs multiple replicas at any given moment, and
each replica responds at a slightly different speed depending on its current
load. The system has an SLA guarantee: if the total round-trip exceeds the
latency budget, the request is dropped and the user sees an error.

Your job is to figure out how many valid ways a request can be routed through
the service chain without breaching the budget.

**Task:** Given a sequential chain of $N$ services where each service has a
list of replica latencies, count the number of ways to pick exactly one replica
per service such that the sum of chosen latencies does not exceed the budget
$B$.

## Input

$$
\begin{array}{l}
N \ \ B \\
k_0\ l_{(0,0)}\ l_{(0,1)}\ \dots\ l_{(0,k_0-1)} \\
k_1\ l_{(1,0)}\ l_{(1,1)}\ \dots\ l_{(1,k_1-1)}
\end{array}
$$

- **Line 1:** Two integers $N$ (number of services) and $B$ (latency budget).
- **Next $N$ lines:** Each line starts with $k_i$ (number of replicas for
  service $i$), followed by $k_i$ space-separated integers: the latency of
  each replica.

## Output

Print a single integer: the number of valid replica combinations whose total
latency is at most $B$.

## Constraints
- $1 \leq N \leq 7$
- $1 \leq k_i \leq 7$
- $1 \leq l_{i,j} \leq 100$
- $1 \leq B \leq 500$
- Time limit: **2 seconds**
- Memory limit: **256 MB**

## Sample Input 1

```
3 40
3 10 20 15
2 5 30
3 8 12 25
```

## Sample Output 1

```
7
```

## Explanation

All valid combinations summing to at most 40:

| Path         | Sum |
|--------------|-----|
| 10 + 5 + 8   | 23  |
| 10 + 5 + 12  | 27  |
| 10 + 5 + 25  | 40  |
| 15 + 5 + 8   | 28  |
| 15 + 5 + 12  | 32  |
| 20 + 5 + 8   | 33  |
| 20 + 5 + 12  | 37  |

## Sample Input 2

```
2 4
2 1 2
2 1 2
```

## Sample Output 2

```
4
```

## Explanation

All four combinations are valid: (1,1)=2, (1,2)=3, (2,1)=3, (2,2)=4.
