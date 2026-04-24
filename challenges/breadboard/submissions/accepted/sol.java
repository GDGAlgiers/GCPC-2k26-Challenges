import java.io.*;
import java.util.*;

public class sol {
    static final int MOD = 1000000007;

    static class DSU {
        int[] parent;
        int components;

        DSU(int n) {
            parent = new int[n + 1];
            for (int i = 1; i <= n; i++) {
                parent[i] = i;
            }
            components = n;
        }

        int find(int i) {
            if (parent[i] == i) return i;
            return parent[i] = find(parent[i]);
        }

        void unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
                components--;
            }
        }
    }

    // Helper class to replace C++ std::pair
    static class Point {
        int r, c;

        Point(int r, int c) {
            this.r = r;
            this.c = c;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Point point = (Point) o;
            return r == point.r && c == point.c;
        }

        @Override
        public int hashCode() {
            return Objects.hash(r, c);
        }
    }

    // Fast I/O class
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    String line = br.readLine();
                    if (line == null) return null; // EOF
                    st = new StringTokenizer(line);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        Integer nextInt() {
            String str = next();
            if (str == null) return null;
            return Integer.parseInt(str);
        }
    }

    public static void main(String[] args) {
        FastReader in = new FastReader();
        PrintWriter out = new PrintWriter(System.out);

        Integer N = in.nextInt();
        if (N == null) return; // Equivalent to checking if cin >> N succeeded
        int M = in.nextInt();
        int Q = in.nextInt();

        // Precompute powers of 2 
        // Array sized dynamically to handle bounds correctly
        long[] power2 = new long[Math.max(100005, N + 1)];
        power2[0] = 1;
        for (int i = 1; i <= N; i++) {
            power2[i] = (power2[i - 1] * 2) % MOD;
        }

        DSU dsu = new DSU(N);
        // Track occupied holes using a HashSet of Points
        HashSet<Point> occupied = new HashSet<>();

        for (int i = 0; i < Q; i++) {
            int r1 = in.nextInt();
            int c1 = in.nextInt();
            int r2 = in.nextInt();
            int c2 = in.nextInt();

            Point p1 = new Point(r1, c1);
            Point p2 = new Point(r2, c2);

            // Check if either hole is already occupied
            if (occupied.contains(p1) || occupied.contains(p2)) {
                // Discard cable, output current configuration
                out.println(power2[dsu.components]);
            } else {
                // Mark holes as occupied and connect columns
                occupied.add(p1);
                occupied.add(p2);
                dsu.unite(c1, c2);
                out.println(power2[dsu.components]);
            }
        }

        out.flush();
    }
}