import java.io.*;
import java.util.*;

class sol {
    static final int M = 1000000007;
    static final int N = 100010;
    static int[] pw = new int[N];

    static int add(int a, int b) {
        return (a + b) % M;
    }

    static int mul(int a, int b) {
        return (int) ((1L * a * b) % M);
    }

    static int sub(int a, int b) {
        return ((a - b) % M + M) % M;
    }

    static class Node {
        int cnt = 0, sum = 0;
        Node() {}
    }

    static Node neutral = new Node();

    static class SegTree {
        SegTree left = null, right = null;
        Node node = new Node();
        int start, end;

        SegTree(int l, int r) {
            this.start = l;
            this.end = r;
        }

        void extend() {
            if (left == null) {
                int mid = start + (end - start) / 2;
                left = new SegTree(start, mid);
                right = new SegTree(mid + 1, end);
            }
        }

        Node pushup(Node a, Node b) {
            Node ret = new Node();
            ret.cnt = add(a.cnt, b.cnt);
            ret.sum = add(a.sum, b.sum);
            return ret;
        }

        void update(int idx, int sum, int cnt) {
            if (start > idx || end < idx) return;
            if (start == end) {
                node.cnt = add(node.cnt, cnt);
                node.sum = add(node.sum, sum);
                return;
            }
            extend();
            left.update(idx, sum, cnt);
            right.update(idx, sum, cnt);
            node = pushup(left.node, right.node);
        }

        Node query(int l, int r) {
            if (r < start || end < l) return neutral;
            extend();
            if (l <= start && end <= r) return node;
            Node leftRes = left.query(l, r);
            Node rightRes = right.query(l, r);
            return pushup(leftRes, rightRes);
        }
    }

    static void solve(FastScanner sc, PrintWriter out) {
        int n = sc.nextInt();
        int[] a = new int[n];
        TreeMap<Integer, Integer> mp = new TreeMap<>();
        
        for (int i = 0; i < n; i++) {
            a[i] = sc.nextInt();
            mp.put(a[i], 1);
        }
        
        int nxt = 1;
        for (Map.Entry<Integer, Integer> entry : mp.entrySet()) {
            mp.put(entry.getKey(), nxt++);
        }

        SegTree root = new SegTree(0, nxt + 5);
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            int x = a[i];
            a[i] = mp.get(x);
            
            Node left = root.query(0, a[i] - 1);
            Node right = root.query(a[i] + 1, nxt + 5);
            
            int cur = sub(mul(left.cnt, x), left.sum);
            cur = add(cur, sub(right.sum, mul(right.cnt, x)));
            ans = add(ans, mul(cur, pw[n - i - 1]));
            root.update(a[i], mul(x, pw[i]), pw[i]);
        }
        out.println(ans);
    }

    public static void main(String[] args) {
        pw[0] = 1;
        for (int i = 1; i < N; i++) {
            pw[i] = (pw[i - 1] << 1) % M;
        }
        
        FastScanner sc = new FastScanner();
        PrintWriter out = new PrintWriter(System.out);
        
        int tc = 1;
        // tc = sc.nextInt();
        while (tc-- > 0) {
            solve(sc, out);
        }
        
        out.flush();
    }
    
    // Custom FastScanner for CP equivalents of fast I/O
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
                    if (line == null) return null;
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
    }
}