---
title: "DzNet Signal Coverage"
author: "Nabil Ghemam Djeridi"
difficulty: "Medium"
---

# DzNet Signal Coverage

A new telecom operator in Algeria wants to deploy its network across multiple cities.
The cities are modeled as a graph where each city is a node, and connections between cities are given by an adjacency matrix.

The company can install a signal tower in any city.
A tower installed in city `i` covers:
- city `i` itself,
- every city directly connected to `i`.

A city may be covered by multiple towers, and some cities may have no connections.

**Task:** Determine the minimum number of signal towers required so that every city is covered.

## Input

The first line contains an integer `N` (`1 <= N <= 20`) — the number of cities.

Each of the next `N` lines contains `N` space-separated integers (`0` or `1`) describing the adjacency matrix.

- `1` means there is a direct connection,
- `0` means there is no direct connection.

## Output

Print one integer: the minimum number of towers needed to cover all cities.

## Constraints

- `1 <= N <= 20`
- Matrix values are only `0` or `1`
- Time limit: **2 seconds**
- Memory limit: **512 MB**

## Sample Input 1

```text
4
0 1 0 0
1 0 1 0
0 1 0 1
0 0 1 0
```

## Sample Output 1

```text
2
```

## Sample Input 2

```text
6
0 1 1 0 0 0
1 0 1 0 0 0
1 1 0 0 0 0
0 0 0 0 1 1
0 0 0 1 0 1
0 0 0 1 1 0
```

## Sample Output 2

```text
2
```

## Sample Input 3

```text
12
0 1 1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 0 0 0 0 0 0 0
1 1 0 0 0 0 0 0 0 0 0 0
0 1 0 0 1 0 0 0 0 0 0 0
0 0 0 1 0 1 1 0 0 0 0 0
0 0 0 0 1 0 1 0 0 0 0 0
0 0 0 0 1 1 0 1 0 0 0 0
0 0 0 0 0 0 1 0 1 1 0 0
0 0 0 0 0 0 0 1 0 1 0 0
0 0 0 0 0 0 0 1 1 0 1 1
0 0 0 0 0 0 0 0 0 1 0 1
0 0 0 0 0 0 0 0 0 1 1 0
```

## Sample Output 3

```text
3
```

## Explanation

In Sample 1, placing towers in cities 2 and 3 (1-based indexing) covers all four cities, and one tower alone is not enough.
