# Card Tricks - Editorial

## Problem Analysis

We need to handle three operations on a collection of 32-bit integers:
1. **Insertion**: Add a number and its bit-reversed counterpart
2. **Retrieval**: Find and remove the largest number ≤ mean of current collection
3. **Flip**: Toggle between using original numbers or their bit-reversed versions

## Algorithm Design

### Data Structures
1. **Two Multisets**: Maintain two collections - one for original values, one for reversed values
2. **Two Sums**: Track sums of both collections for efficient mean calculation
3. **State Flag**: Boolean to track whether we're using original or reversed values

### Operations

1. **Insertion (Type 1)**:
   - Compute bit-reversed value of input
   - Based on current state, insert original into one multiset and reversed into the other
   - Update corresponding sums

2. **Retrieval (Type 2)**:
   - Calculate mean (sum/size) of current collection
   - Find largest value ≤ mean using upper_bound
   - Remove this value from both collections
   - Update sums accordingly

3. **Flip (Type 3)**:
   - Toggle the state flag

### Bit Reversal
- For each bit position i (0-15):
  - Swap bit i with bit (31-i)
  - Preserve the original bit values during swap

## Complexity Analysis
- **Time**: O(log n) per operation (multiset operations)
- **Space**: O(n) to store all elements

## Language-Specific Implementations

### C++
- Use `std::multiset` for ordered collections
- Use `std::upper_bound` for efficient searching
- Maintain sums as `long long` to prevent overflow

### C
- Implement balanced BST (like AVL or Red-Black tree) for ordered collections
- Implement binary search for finding elements
- Track sums separately

### Python
- Use `SortedList` from `bisect` module or third-party libraries
- Maintain sums as separate variables
- Implement bit reversal with bitwise operations

### Go
- Use `container/list` with custom sorting or third-party BST implementations
- Maintain sums as separate variables
- Implement bit reversal with bitwise operations

### JavaScript
- Use arrays with custom sorting for each operation
- Maintain sums separately
- Implement bit reversal with bitwise operations
- Note: JS may be less efficient for large inputs due to lack of built-in ordered collections

### **Java**:
- Uses `TreeSet` for O(log n) operations
- Built-in `floor()` method simplifies finding the largest element ≤ mean
- Efficient I/O handling with `BufferedReader` and `PrintWriter`


## Key Implementation Notes
1. **Bit Reversal**: Must handle 32-bit unsigned integers correctly
2. **Mean Calculation**: Use integer division (floor division)
3. **Multiset Operations**: Ensure O(log n) time complexity for insertions, deletions, and searches
4. **State Management**: Cleanly toggle between original and reversed values

The algorithm efficiently handles all operations while maintaining the required constraints, making it suitable for large input sizes.


Here's a Java implementation of the Card Tricks problem, followed by the editorial addition:

```java
import java.util.*;
import java.io.*;

public class CardTricks {
    static int rev(int x) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            if ((x & (1 << i)) != 0) {
                res |= (1 << (31 - i));
            }
        }
        return res;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int q = Integer.parseInt(br.readLine());

        // Using TreeSet with custom comparator to maintain sorted order
        TreeSet<Integer> set1 = new TreeSet<>();
        TreeSet<Integer> set2 = new TreeSet<>();
        long sum1 = 0, sum2 = 0;
        boolean bl = true; // state flag

        for (int i = 0; i < q; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int typ = Integer.parseInt(st.nextToken());

            if (typ == 1) {
                int x = Integer.parseInt(st.nextToken());
                int x2 = rev(x);

                if (bl) {
                    set1.add(x);
                    set2.add(x2);
                    sum1 += x;
                    sum2 += x2;
                } else {
                    set2.add(x);
                    set1.add(x2);
                    sum2 += x;
                    sum1 += x2;
                }
            } else if (typ == 2) {
                if (bl) {
                    if (set1.isEmpty()) continue;
                    long mean = sum1 / set1.size();
                    Integer val = set1.floor((int) mean);
                    if (val == null) continue;

                    out.println(val);
                    sum1 -= val;
                    set1.remove(val);

                    int x2 = rev(val);
                    sum2 -= x2;
                    set2.remove(x2);
                } else {
                    if (set2.isEmpty()) continue;
                    long mean = sum2 / set2.size();
                    Integer val = set2.floor((int) mean);
                    if (val == null) continue;

                    out.println(val);
                    sum2 -= val;
                    set2.remove(val);

                    int x2 = rev(val);
                    sum1 -= x2;
                    set1.remove(x2);
                }
            } else if (typ == 3) {
                bl = !bl;
            }
        }
        out.flush();
    }
}
```
