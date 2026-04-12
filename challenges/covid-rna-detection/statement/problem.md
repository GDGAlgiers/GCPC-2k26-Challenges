---
title: "COVID-19 RNA Detection"
author: "Ghemam Nabil"
difficulty: "Easy"
---

A lab technician is analyzing RNA sequences to detect whether a person is infected
with COVID-19. The technician compares the given RNA sequence against a list of known
COVID-19 genetic markers.

**Task:** Given an RNA sequence, determine whether it contains any of the known
SARS-CoV-2 RNA markers.

## Note

- The RNA sequence can be up to **1000 characters** long.
- Only the characters `A`, `C`, `G`, and `U` are present.
- The known COVID-19 RNA markers are:

| # | Marker       |
|---|--------------|
| 1 | `ACGUAUGC`   |
| 2 | `AUGCGUAG`   |
| 3 | `UGCUAGCU`   |

## Input

A single line containing the RNA sequence — a non-empty string of characters from
$\{A, C, G, U\}$.

## Output

Print `True` if the RNA sequence contains any of the known markers, or `False` otherwise.

## Constraints

| Parameter | Constraint |
|-----------|------------|
| $|s|$ | $1 \leq |s| \leq 1000$ |
| Alphabet | $A, C, G, U$ only |
| Time limit | **2 seconds** |
| Memory limit | **256 MB** |

## Examples

| Input | Output |
|-------|--------|
| `AGUCGACGUACGUAUGCUGCAU` | `True` |
| `UCGUAGCUAGCUACUAGCUGAC` | `False` |

## Explanation

In the first example, the marker `ACGUAUGC` appears starting at position 10 (0-indexed).

In the second example, none of the three markers appear in the sequence.
