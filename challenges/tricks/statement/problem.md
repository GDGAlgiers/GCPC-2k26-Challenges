---
title: "Card Tricks"
author: "Raouf Ould Ali"
difficulty: "Hard"
---

<!--
  RENDER PDF (run from inside the challenge directory, not statement/):
    ../../scripts/render-pdf.sh

  Requirements: pandoc + texlive-xetex
    sudo apt install pandoc texlive-xetex texlive-fonts-recommended texlive-latex-extra
-->

# Card Tricks

<!-- Story / flavor text. 1–2 paragraphs to set the scene. Keep it engaging but concise. -->

During summer vacation, when Red1 recieved his new deck of binary edition bicycle playing cards, he thought it would be a waste of their quality not to learn a few card tricks. After practicing for a few weeks, he learned the following three techniques:

- The __first__ technique is fast insert that lets him insert any card of value $v$ and shuffle the deck at lightning speed.
- The __second__ technique is a quick retrieval that lets him find the biggest card of value $x$ such that its value is less than or equal to the mean value of the cards currently in the deck. After this, he always opts to remove the card from the deck to make the trick seem more genuine. The card will always be shown when it is removed.
- The __third__ and last trick is a spreading trick that lets him flip all of the cards in his deck at a snap of his fingers. This reveals the labels on the back of these cards which, for each card of value $v$, has a value $v'$ such that it has all of the bits of $v$ reversed when $v$ is interpreted as a 32-bit unsigned integer. <br>To reverse the bits of a number, you take its binary representation and swap the bits in positions $i$ and $31 - i$. For example, the number $(3)_{10} = (...011)_{2}$ becomes $(110...)_2 = (3221225472)_{10}$ and $(5)_{10} = (...0101)_2$ becomes $(1010...)_{2} = (2684354560)_{10}$.

Red1's friends are quite impressed by these tricks, but they are doubtful of his sleight of hand. They would like to test him by having him do these tricks $Q$ times. Simulate each of the queries in order and for each query of the second trick, output the card that Red1 shows to his friends.

**Task:** For each query of the second trick, output the card that Red1 shows to his friends.

## Input

The type of each query is either $1, 2,$ or $3$ corresponding to the first, second and third tricks respectively. When the query is $1$, there is an additional value to be read that corresponds to the label of the card being inserted. 

Let $T[i]$ be the type of the $i$th query and $V[i]$ be the value of the card inserted when $T[i] = 1$, $O[i]$ be the answer to the $i$th query of type $2$, and $Q_2$ be the number of queries of type 2. 
```
Q
T[0] // query of type 2 or 3
T[1] V[1] // query of type 1
...
T[Q-1]
```

The first line contains a single integer $n$ ($1 \leq n \leq 10^5$).

The second line contains $n$ space-separated integers $a_1, a_2, \ldots, a_n$
($1 \leq a_i \leq 10^9$).

## Output

```
O[0]
...
O[Q2-1]
```

## Constraints

- $Q \leq 10^5$
- $v_i \leq 2^{32} -1$
- Time limit: **2 seconds**
- Memory limit: **512 MB**

## Sample Input 1

```
6
1 1
1 2
1 3
2
3
2
```

## Sample Output 1

```
2
2147483648
```

