---
title: "Circuit Breaker"
author: "Bouzara Zakaria"
difficulty: "Medium"
---

# Circuit Breaker

It is 2:47 AM. The on-call engineer gets paged: response times are spiking, users are seeing errors, and the dashboard is a sea of red. At the heart of modern distributed systems lies a safety mechanism called the **circuit breaker**: when a service fails too many times within a short window, its circuit "opens" and all further requests are rejected immediately, giving it time to recover. After a cooldown period the circuit "closes" and traffic resumes normally.

You have been handed the event logs of a live production system. Replay those logs and answer the SRE team's queries: at a given point in time, is a given service available?

**Task:** Given a sequence of timestamped service events and a list of queries, output for each query whether the target service's circuit is `OPEN` or `CLOSED` at that moment.

## Input

```
nbservices = N, threshold = X, window = W, cooldown = C
events = [T, S, R]
queries = [T, S]
```

- **Line 1:** Four integers: number of services $N$, failure window $W$ (seconds), failure threshold $X$, and cooldown duration $C$ (seconds).
- **Events lines:** Each event is a triple $T$ $S$ $R$: timestamp, service ID, and result ($0$ = failure, $1$ = success). Events are sorted by $T$.
- **Queries lines:** Each query is a pair $T$ $S$: timestamp and service ID.

## Output

For each query print `OPEN` if the service's circuit is tripped at time $T$, or `CLOSED` if it is available. A circuit opens the moment a service accumulates $X$ failures within any sliding window of $W$ seconds. It stays open for $C$ seconds, then closes. Events that arrive while a circuit is open are ignored and do not count toward the failure window.

## Constraints

- $1 \leq N \leq 100$
- $1 \leq E, Q \leq 10^5$
- $0 \leq T \leq 10^9$
- $1 \leq W, C \leq 10^6$
- $1 \leq X \leq 10^4$
- Time limit: **2 seconds**
- Memory limit: **256 MB**

## Example Input

```
N=2, W=10, X=3, C=15
events = [(0, 0, 0), (3, 0, 0), (7, 0, 0), (10, 0, 0), (12, 0, 1), (20, 0, 0), (25, 1, 0),]
queries = [(8, 0), (9, 0), (22, 0), (23, 0), (25, 1),]
```

## Example Output

```
OPEN, OPEN, CLOSED, CLOSED, CLOSED,
```

## Explanation

Service 0 receives failures at $t=0$, $t=3$, and $t=7$. All three fall within the window $[0, 10]$, hitting the threshold $X=3$, so the circuit opens at $t=7$ and stays open until $t=7+15=22$. Events at $t=10$, $t=12$, and $t=20$ arrive while the circuit is open and are ignored. At $t=22$ the circuit closes. Service 1 only has one failure at $t=25$, well below the threshold.
