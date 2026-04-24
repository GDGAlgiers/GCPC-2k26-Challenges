---
title: "Dungeon Escape"
author: "Lyes Boudjabout"
difficulty: "Easy"
---


# Dungeon Escape

You awake in a damp, torchlit dungeon with no memory of how you got there. The only way out is through a maze of corridors, but some doors are locked. Rumour has it that a single rusty key lies somewhere in the dungeon, capable of opening every locked door. Time is of the essence — every step counts.

**Task:** Find the minimum number of steps required to reach the exit, or determine that escape is impossible.

## Input

The first line contains two integers $N$ and $M$ ($1 \le N, M \le 500$) — the number of rows and columns in the dungeon grid.

The next $N$ lines each contain a string of length $M$ consisting of the following characters:

- `.` — an empty, passable cell
- `#` — a wall (impassable)
- `K` — a locked door; you may only pass through it if you are carrying the key
- `k` — the key; stepping on this cell automatically picks it up, permanently unlocking all locked doors
- `S` — your starting position (exactly one exists)
- `E` — the exit (exactly one exists)

You can move up, down, left, or right by one cell per step.

It is guaranteed that there is **at most one** key in the dungeon.

## Output

Print a single integer — the minimum number of steps to reach `E` from `S`. If it is impossible, print `-1`.

## Constraints

- $1 \le N, M \le 500$
- At most one `k` exists in the grid.
- Exactly one `S` and one `E` are present.
- Time limit: **1 second**
- Memory limit: **256 MB**

## Sample Input 1

```
5 5
S...K
###.#
k...E
###.#
.....
```

## Sample Output 1

```
6
```

## Explanation

The grid contains a key and a locked door, but the shortest path from $S$ to $E$ does not require using them. The player can move right three times, down twice, and right once to reach the exit in 6 steps. The locked door $K$ and key $k$ are not used in this optimal route.

## Sample Input 2

```
3 5
S...K
#k##E
...#.
```

## Sample Output 2

```
7
```

## Explanation

The grid contains a key and a locked door. The shortest path from $S$ to $E$ requires the player to first collect the key, then pass through the locked door. The player moves right to $(0,1)$, down to $(1,1)$ to pick up the key, back up to $(0,1)$, right three times through $(0,2)$, $(0,3)$, and the now‑unlocked door $K$ at $(0,4)$, and finally down to $(1,4)$ to reach the exit in $7$ steps. The locked door $K$ blocks the direct top‑row route, making the key mandatory for an optimal solution.
