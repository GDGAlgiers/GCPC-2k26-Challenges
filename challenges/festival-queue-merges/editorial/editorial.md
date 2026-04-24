# Festival Queue Merges - Editorial

## Tags
`implementation` `ad-hoc` `priority_queue`

## Key Observation
> Only one or two gate counts change per operation, so we can update those gates in a max-heap and answer each `QUERY` by cleaning stale heap entries lazily.

## Data Structures
- `cnt[g]` (1-indexed array): the current number of people at gate `g`.
- Max-heap `pq` of pairs `(value, -gate)`:
  - larger `value` comes first (busiest gate),
  - if values are equal, larger `-gate` comes first, i.e. smaller gate index.

So a heap top `(14, -2)` beats `(14, -4)`, which matches the tie-break rule.

## Algorithm
1. Initialize `cnt[g] = 0` for all gates.
2. Push `(0, -g)` for every gate into the heap.
3. For each operation:
   - `ADD g x`: `cnt[g] += x`, then push `(cnt[g], -g)`.
   - `SERVE g x`: `t = min(cnt[g], x)`, `cnt[g] -= t`, push new state.
   - `MOVE a b x`: `t = min(cnt[a], x)`, decrease `a`, increase `b`, push both.
   - `MERGE a b`: `cnt[a] += cnt[b]`, `cnt[b] = 0`, push both.
   - `QUERY`:
     - While heap top `(v, neg_g)` is stale (`v != cnt[-neg_g]`), pop it.
     - First non-stale top is exactly the answer.

This is lazy deletion: we never remove old entries when updates happen; we discard them only when they reach the top.

## Why This Is Correct
We maintain two invariants:
1. `cnt[g]` is always the true queue size of gate `g` after processing operations so far.
2. For every gate `g`, the heap contains at least one entry `(cnt[g], -g)` corresponding to its latest value.

Invariant 1 holds because each operation directly simulates the statement.
Invariant 2 holds because every time a gate changes, we push its new pair.

Now consider a `QUERY`:
- Any stale top is safe to remove: it describes an old value that no longer equals `cnt[g]`.
- Because invariant 2 guarantees a fresh entry for every gate, removing stale entries cannot remove all candidates for the true maximum.
- The first fresh top has maximum value, and among ties the smallest index, due to pair ordering `(value, -gate)`.

Therefore each `QUERY` prints exactly the required gate and queue size.

## Complexity
- **Time:** $O((K + Q)\log(K + Q))$ total.
  - Each update pushes at most 2 heap entries: at most `K + 2Q` pushes.
  - Each entry is popped at most once (when stale and reaches top).
  - Every push/pop is logarithmic in heap size.
- **Space:** $O(K + Q)$ for `cnt` and heap entries.

## Step-by-Step on Sample
Start: `cnt = [0, 0, 0, 0]` (gates 1..4).

1. `ADD 1 5` -> `[5, 0, 0, 0]`
2. `ADD 2 3` -> `[5, 3, 0, 0]`
3. `QUERY` -> busiest is gate `1` with `5` -> print `1 5`
4. `MOVE 1 2 4` -> move `4`, now `[1, 7, 0, 0]`
5. `QUERY` -> print `2 7`
6. `SERVE 2 2` -> `[1, 5, 0, 0]`
7. `ADD 3 9` -> `[1, 5, 9, 0]`
8. `MERGE 2 3` -> gate 2 gets all of gate 3 -> `[1, 14, 0, 0]`
9. `QUERY` -> print `2 14`
10. `ADD 4 14` -> `[1, 14, 0, 14]`
11. `QUERY` -> tie (gates 2 and 4), pick smaller index -> print `2 14`

## Common Pitfalls
- Forgetting `SERVE` and `MOVE` are capped by available people (`min(current, x)`).
- Implementing tie-break incorrectly. Use `(count, -index)` in a max-heap.
- Trying to erase old heap entries eagerly (hard in binary heap); lazy deletion is simpler and fast enough.
- Using 32-bit integers. With up to `2e5` additions of size `1e9`, totals can reach about `2e14`, so use `long long` / 64-bit.

## Alternatives
- Full scan on each `QUERY`: `O(K)` per query, worst-case `O(KQ)` -> too slow for `2e5`.
- Balanced BST keyed by `(count, -index)`: also works in `O(log K)` per update/query, but needs explicit delete+insert on every change; heap + lazy deletion is shorter and less error-prone.
