---
title: "Midnight Relay Tour"
author: "tarek-ait"
difficulty: "Medium-Hard"
---


# Midnight Relay Tour

Minutes before the GCPC live stream goes on air, a thunderstorm knocks several
relay stations offline across the city. Nadia starts at the backup control hub
in city $1$, and the final broadcast center is in city $n$.

There are $k$ damaged relays, each located in a different city. Nadia must
visit every one of those cities at least once to reboot the relay manually.
After repairing all of them, she must continue to city $n$. The road network is
bidirectional, every road has a travel time, and Nadia may pass through the
same city or road multiple times if that leads to a faster overall route.

**Task:** Compute the minimum total travel time needed to start at city $1$,
visit all damaged relay cities in any order, and finish at city $n$.
If this is impossible, print `-1`.

## Input

The first line contains three integers $n$, $m$, and $k$:

- $n$ — the number of cities
- $m$ — the number of roads
- $k$ — the number of damaged relays

The second line contains $k$ distinct integers
$c_1, c_2, \ldots, c_k$ — the cities containing damaged relays.

Each of the next $m$ lines contains three integers $u$, $v$, and $w$,
describing a bidirectional road between cities $u$ and $v$ with travel time
$w$.

## Output

Print a single integer:

- the minimum total travel time, or
- `-1` if Nadia cannot visit all damaged relays and still reach city $n$.

## Sample Input 1

```text
6 9 2
3 5
1 2 4
1 3 2
2 3 1
2 4 7
3 4 3
3 5 8
4 5 2
4 6 5
5 6 1
```

## Sample Output 1

```text
8
```

## Sample Input 2

```text
5 3 2
2 4
1 2 3
2 3 4
4 5 1
```

## Sample Output 2

```text
-1
```

## Explanation

In the first sample, an optimal route is:

$$
1 \rightarrow 3 \rightarrow 4 \rightarrow 5 \rightarrow 6
$$

with total travel time

$$
2 + 3 + 2 + 1 = 8.
$$

This route visits both damaged relays (`3` and `5`) before reaching city `6`.

In the second sample, the graph is split into two disconnected components, so
it is impossible to visit relay city `4` after starting from city `1`.
