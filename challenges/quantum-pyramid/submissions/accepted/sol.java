import java.io.*;
import java.util.*;

public class sol {
    // Node class to mimic the C++ struct
    static class Node {
        long c;
        int q; // 0, 1, or 2 (superposition)

        Node(long c, int q) {
            this.c = c;
            this.q = q;
        }
    }

    // Associative merge operation
    static Node mergeNodes(Node a, Node b) {
        if (a.c > b.c) return a;
        if (a.c < b.c) return b;
        if (a.q == b.q) return a;
        return new Node(a.c, 2);
    }

    public static void main(String[] args) throws IOException {
        // Fast I/O using BufferedReader and StringTokenizer
        FastReader sc = new FastReader(System.in);
        PrintWriter out = new PrintWriter(System.out);

        int n = sc.nextInt();
        int Q = sc.nextInt();

        // Calculate maxLog: floor(log2(n)) + 1
        int maxLog = 32 - Integer.numberOfLeadingZeros(n);
        Node[][] st = new Node[maxLog][n + 1];

        // Level 0 of Sparse Table
        for (int i = 1; i <= n; i++) {
            long a = sc.nextLong();
            st[0][i] = new Node(a / 2, (int) (a % 2));
        }

        // Build Sparse Table
        for (int p = 1; p < maxLog; p++) {
            for (int i = 1; i + (1 << p) - 1 <= n; i++) {
                st[p][i] = mergeNodes(st[p - 1][i], st[p - 1][i + (1 << (p - 1))]);
            }
        }

        // Process Queries
        for (int q = 0; q < Q; q++) {
            int k = sc.nextInt();
            int r = sc.nextInt();

            int L = k;
            int R = k + r - 1;

            // O(1) Range Query
            int diff = R - L + 1;
            int p = 31 - Integer.numberOfLeadingZeros(diff);
            Node res = mergeNodes(st[p][L], st[p][R - (1 << p) + 1]);

            long baseVal = res.c * 2;

            if (res.q == 0) {
                out.println(baseVal);
            } else if (res.q == 1) {
                out.println(baseVal + 1);
            } else {
                out.println(baseVal + " " + (baseVal + 1));
            }
        }
        out.flush();
    }

    // FastReader class for high-performance input parsing
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader(InputStream in) {
            br = new BufferedReader(new InputStreamReader(in));
        }

        String next() {
            while (st == null || !st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    return null;
                }
            }
            return st.nextToken();
        }

        int nextInt() { return Integer.parseInt(next()); }
        long nextLong() { return Long.parseLong(next()); }
    }
}