# COVID-19 RNA Detection — Editorial

## Tags
`string-search` `substring` `implementation`

## Key Observation
> The problem reduces to a plain substring search: check whether any of the 3 fixed
> markers appears anywhere inside the input string. No sorting, no math, no data
> structures — just `str.find()` / `str.contains()` / `strstr()`.

## Approach
1. Read the RNA sequence as a single string.
2. For each of the 3 known markers (`ACGUAUGC`, `AUGCGUAG`, `UGCUAGCU`), check
   whether it is a contiguous substring of the input.
3. If any marker is found, print `True` and stop. Otherwise print `False`.

## Complexity
- **Time:** $O(n \cdot m)$ where $n \leq 1000$ (RNA length) and $m = 8$ (marker length).
  Effectively $O(n)$ in practice — trivial on modern hardware.
- **Space:** $O(1)$ beyond storing the input.

## Common Pitfalls
- Printing `true` / `false` (lowercase) instead of `True` / `False` — the judge is
  case-sensitive.
- Reading input with `getline` after `cin >>` without flushing the newline buffer
  (C++ / Java).
- Forgetting that the same sequence may contain multiple markers — but you only need
  to find one, so short-circuit early.

## Example Walkthrough
Input: `AGUCGACGUACGUAUGCUGCAU`

Scan for `ACGUAUGC`:
```
Position 0:  AGUCGACG  ≠ ACGUAUGC
Position 1:  GUCGACGU  ≠
...
Position 9:  ACGUAUGC  ✓  → print True
```

## Alternative Approaches
- **KMP / Aho-Corasick**: overkill — the input is at most 1000 chars and markers are
  fixed 8-char strings. Naive `O(n·m)` is fine.
- **Regex**: works but unnecessarily heavy for a competitive programming judge.
