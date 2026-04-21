# The Sarrus Oracle - Editorial

## Tags
`number-theory` `sieve` `prefix-sums`

## Theory
The whole problem is built on a true statement and its false converse.

For every prime number $p$ and every integer $a$, Fermat's little theorem gives:

$$a^p \equiv a \pmod p.$$

This problem uses the specific choice $a = 2$, so the oracle checks whether

$$2^n \equiv 2 \pmod n.$$

The oracle makes the incorrect reverse assumption:

> if $2^n \equiv 2 \pmod n$, then $n$ must be prime

That is false. Some composite numbers also satisfy the same congruence. Those
are exactly the numbers counted by this problem.

Example:

- $341 = 11 \times 31$ is composite
- yet $2^{341} \equiv 2 \pmod{341}$

So `341` fools the oracle and is counted.

## Key Observation
> Once we know the largest queried right endpoint, we can precompute every
> Sarrus number up to that bound and answer each interval query with a prefix
> sum.

## Approach
Let $M = \max R$ over all queries.

1. Read all queries first and compute $M$.
2. Run a sieve of Eratosthenes up to $M$ to mark prime numbers.
3. For every integer $n$ from `2` to `M`:
   - skip it if it is prime, because Sarrus numbers must be composite
   - compute $2^n \bmod n$ with binary exponentiation
   - mark `is_sarrus[n] = 1` if the result is `2`
4. Build a prefix array:

   $$pref[i] = \text{number of Sarrus numbers in } [2, i]$$

5. Each query `[L, R]` is answered in constant time:

   $$pref[R] - pref[L - 1]$$

The statement already gives the number-theory background:

- every prime satisfies $2^p \equiv 2 \pmod p$
- some composites also satisfy it
- only those composite ones count

So the goal is to precompute the oracle's false positives over one prefix of
the integers, then answer intervals quickly.

## Why Binary Exponentiation
We never want to compute the full value of $2^n$, because it is enormous.

Instead, we compute $2^n \bmod n$ directly with repeated squaring:

- square the current base
- reduce modulo $n$ after every multiplication
- use the binary form of the exponent

That reduces the work for one test from linear in `n` down to logarithmic in
`n`.

## Bonus Math Note
There is a deeper family of impostor numbers called Carmichael numbers, and
they admit a stronger theorem-based characterization. That is an interesting
extension, but it does **not** solve this exact judged problem by itself,
because this problem counts all base-2 false positives, not only that stronger
subfamily.

## Complexity
- **Time:** $O(M \log \log M + M \log M + q)$
- **Space:** $O(M)$

## Common Pitfalls
- Counting prime numbers even though they satisfy the congruence too
- Recomputing the answer independently for each query instead of preprocessing
- Forgetting to use `pref[L - 1]` when subtracting prefix sums
- Trying to build the full number $2^n$ instead of computing it modulo $n$

## Example Walkthrough
For the sample queries:

- `[300, 400]` contains only one Sarrus number: `341`
- `[500, 700]` contains `561` and `645`
- `[1000, 2000]` contains `1105`, `1387`, `1729`, and `1905`

After preprocessing, each of these is just one prefix subtraction.

## Alternative Approaches
- With much smaller constraints, each query could be handled by direct testing
- With much larger limits, this exact precomputation would become too expensive
  and a different counting strategy would be needed
