import java.io.*;
import java.util.*;

public class sol {
    private static final class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        FastScanner(InputStream is) {
            in = is;
        }

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        String next() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            StringBuilder sb = new StringBuilder();
            while (c > ' ') {
                sb.append((char) c);
                c = read();
            }
            return sb.toString();
        }

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            long sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            long val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }

    private static final class Node {
        long c;
        int neg;

        Node(long c, int neg) {
            this.c = c;
            this.neg = neg;
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int k = (int) fs.nextLong();
        int q = (int) fs.nextLong();

        long[] cnt = new long[k + 1];
        PriorityQueue<Node> pq = new PriorityQueue<>((a, b) -> {
            if (a.c != b.c) return Long.compare(b.c, a.c);
            return Integer.compare(b.neg, a.neg);
        });

        for (int i = 1; i <= k; i++) pq.offer(new Node(0, -i));

        for (int i = 0; i < q; i++) {
            String op = fs.next();

            if (op.equals("ADD")) {
                int g = (int) fs.nextLong();
                long x = fs.nextLong();
                cnt[g] += x;
                pq.offer(new Node(cnt[g], -g));
            } else if (op.equals("SERVE")) {
                int g = (int) fs.nextLong();
                long x = fs.nextLong();
                long t = Math.min(cnt[g], x);
                cnt[g] -= t;
                pq.offer(new Node(cnt[g], -g));
            } else if (op.equals("MOVE")) {
                int a = (int) fs.nextLong();
                int b = (int) fs.nextLong();
                long x = fs.nextLong();
                long t = Math.min(cnt[a], x);
                cnt[a] -= t;
                cnt[b] += t;
                pq.offer(new Node(cnt[a], -a));
                pq.offer(new Node(cnt[b], -b));
            } else if (op.equals("MERGE")) {
                int a = (int) fs.nextLong();
                int b = (int) fs.nextLong();
                cnt[a] += cnt[b];
                cnt[b] = 0;
                pq.offer(new Node(cnt[a], -a));
                pq.offer(new Node(cnt[b], -b));
            } else {
                while (true) {
                    Node top = pq.peek();
                    int idx = -top.neg;
                    if (top.c == cnt[idx]) {
                        out.append(idx).append(' ').append(top.c).append('\n');
                        break;
                    }
                    pq.poll();
                }
            }
        }

        System.out.print(out);
    }
}
