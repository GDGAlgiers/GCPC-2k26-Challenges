# Circuit Breaker — Editorial

## Tags
`sliding window` `simulation` `binary search`

## Key Observation
> Each service is independent. Simulate each one's failure log with a sliding
> window to record when its circuit opens and closes, then answer every query
> with a binary search over those intervals.

## Approach

1. **Group events by service.** Since input is already sorted by timestamp,
   each per-service log is sorted for free.

2. **Simulate per service with two pointers.** Walk the failure-only events
   with a sliding window of size $W$. The moment the window accumulates $X$
   failures, record an open interval $[T_o,\ T_o + C)$ where $T_o$ is the
   timestamp of the $X$-th failure, then skip all events that fall inside that
   interval and reset the window. Repeat until all events are consumed.

3. **Answer queries with binary search.** For each query $(T, S)$, binary
   search service $S$'s interval list for any interval containing $T$. Return
   `OPEN` if found, `CLOSED` otherwise.

## Complexity
- **Time:** $O((E + Q) \log E)$
- **Space:** $O(E)$

## Common Pitfalls
- Events that arrive inside an open interval must be **completely skipped**
  before entering the window, not just ignored in the count.
- The cooldown boundary is **half-open** $[T_o, T_o + C)$: a query at exactly
  $T_o + C$ is `CLOSED`.
- Queries are **not sorted**, so you cannot use a running pointer; binary
  search is required.
- Timestamps reach $10^9$, never index arrays by time value.

## Alternative Approaches
**Brute force** $O(E \cdot Q)$: replay each service's log from scratch per
query. Correct but $10^{10}$ operations worst case, too slow.

**Offline query sweep** $O((E+Q) \log E)$: sort queries by timestamp and sweep
events and queries together, avoiding explicit interval storage. Same
complexity, harder to implement.
