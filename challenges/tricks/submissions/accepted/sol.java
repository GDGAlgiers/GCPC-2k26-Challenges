import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
import java.util.TreeMap;

public class sol {
    
    // Exactly replicating the bit-reversal logic
    static long rev(long x) {
        for (long i = 0; i < 16; i++) {
            long tmp = x & (1L << (31 - i));
            if ((x & (1L << i)) != 0) {
                x |= (1L << (31 - i));
            } else {
                if ((x & (1L << (31 - i))) != 0) {
                    x ^= (1L << (31 - i));
                }
            }

            if (tmp != 0) {
                x |= (1L << i);
            } else {
                if ((x & (1L << i)) != 0) {
                    x ^= (1L << i);
                }
            }
        }
        return x;
    }

    // Equivalent to multiset.insert(x)
    static void add(TreeMap<Long, Integer> map, long x) {
        map.put(x, map.getOrDefault(x, 0) + 1);
    }

    // Equivalent to multiset.erase(iterator) -> Removes exactly ONE instance
    static void remove(TreeMap<Long, Integer> map, long x) {
        int count = map.get(x);
        if (count == 1) {
            map.remove(x);
        } else {
            map.put(x, count - 1);
        }
    }

    public static void main(String[] args) {
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);

        long q = sc.nextLong();
        
        TreeMap<Long, Integer> st1 = new TreeMap<>();
        TreeMap<Long, Integer> st2 = new TreeMap<>();
        long sum1 = 0, sum2 = 0;
        boolean bl = true;
        int size = 0;

        while (q-- > 0) {
            int typ = sc.nextInt();
            
            if (typ == 1) {
                long x = sc.nextLong();
                long x2 = rev(x);
                if (bl) {
                    add(st1, x);
                    add(st2, x2);
                    sum1 += x;
                    sum2 += x2;
                } else {
                    add(st2, x);
                    add(st1, x2);
                    sum2 += x;
                    sum1 += x2;
                }
                size++;
            } 
            else if (typ == 2) {
                if (bl) {
                    long men = sum1 / size;
                    
                    // Equivalent to st1.upper_bound(men) then stepping back by 1 iterator
                    long val = st1.floorKey(men);
                    out.println(val);
                    sum1 -= val;
                    
                    long x2 = rev(val);
                    remove(st1, val);
                    
                    // Equivalent to st2.erase(st2.lower_bound(x2))
                    remove(st2, x2);
                    sum2 -= x2;
                } else {
                    long men = sum2 / size;
                    
                    long val = st2.floorKey(men);
                    out.println(val);
                    sum2 -= val;
                    
                    long x2 = rev(val);
                    remove(st2, val);
                    remove(st1, x2);
                    sum1 -= x2;
                }
                size--;
            } 
            else if (typ == 3) {
                bl = !bl;
            }
        }
        
        out.flush(); // Crucial to flush PrintWriter at the end
    }

    // Fast I/O Template
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null) break;
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }
    }
}