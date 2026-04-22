---
title: "AI Simulation on Uncle Island"
author: "Firas Mohamed Elamine Kiram"
difficulty: "Hard"
---

<!--
  RENDER PDF (run from inside the challenge directory, not statement/):
    ../../scripts/render-pdf.sh

  Requirements: pandoc + texlive-xetex
    sudo apt install pandoc texlive-xetex texlive-fonts-recommended texlive-latex-extra
-->

# AI Simulation on Uncle Island

In the year 2125, Firas and Riccardo are lead researchers at the Virtual Earth Lab. Their latest project simulates an island environment called Uncle Island, a polygonal landmass on a 2D grid designed to study AI-driven population behavior. The island's shape is encoded as a simple polygon, where every interior angle is either **90°** or **270°**.

Inside this digital world, AI citizens occupy every integer point inside the polygon — each point represents a smart house with one autonomous resident. Each simulated morning, a random non-empty subset of AI citizens is selected by the training model to perform the daily task of resource foraging, analogous to fishing. Each selected citizen moves to the nearest coastal point — defined as a point with integer coordinates that lies on the polygon's edge. Movement is determined by Manhattan distance:

$$d = |p_x - q_x| + |p_y - q_y|$$

where $(p_x, p_y)$ is the AI citizen's location, and $(q_x, q_y)$ is the closest point on the island's edge.

To optimize neural efficiency and energy modeling, Firas and Riccardo want to calculate:

**Task:** Compute the expected value of the maximum distance walked by any AI citizen during a resource-foraging simulation, assuming each non-empty subset of citizens is equally likely to be chosen.

## Input

The first line contains a single integer $N$, the number of vertices of the polygon ($4 \leq N \leq 2 \times 10^6$).

Each of the next $N$ lines contains $p_x$ and $p_y$, the coordinates of the polygon points sorted in either clockwise or counterclockwise order ($0 \leq p_x, p_y \leq 2 \times 10^3$).

It is guaranteed that the polygon is simple, and each point shares its $x$ or $y$ coordinate with the previous point.

## Output

Output a single value — the expected value of the largest distance walked by a single citizen modulo $998244353$.

Formally, it can be shown that the answer can be expressed as an irreducible fraction $\frac{p}{q}$, where $p$ and $q$ are integers and $q \not\equiv 0 \pmod{998244353}$. Output the integer $p \cdot q^{-1} \bmod 998244353$.

## Constraints

- $4 \leq N \leq 2 \times 10^6$
- $0 \leq p_x, p_y \leq 2 \times 10^3$
- Time limit: **3 seconds**
- Memory limit: **512 MB**

## Sample Input 1

```
4
0 0
2 0
2 2
0 2
```

## Sample Output 1

```
169955497
```

## Explanation

The polygon is a 2×2 square. The interior integer points and their Manhattan distances to the nearest edge are the starting point for computing the expected maximum over all non-empty subsets. The expected value expressed as $p \cdot q^{-1} \bmod 998244353$ gives $169955497$.