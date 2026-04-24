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

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ');

            int sign = 1;
            if (c == '-') {
                sign = -1;
                c = read();
            }

            int val = 0;
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = read();
            }
            return val * sign;
        }
    }

    private static final class Box {
        int d;
        int w;

        Box(int d, int w) {
            this.d = d;
            this.w = w;
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        StringBuilder out = new StringBuilder();

        int n = fs.nextInt();
        Box[] boxes = new Box[n];
        for (int i = 0; i < n; i++) {
            int w = fs.nextInt();
            int d = fs.nextInt();
            boxes[i] = new Box(d, w);
        }

        Arrays.sort(boxes, (a, b) -> {
            if (a.d != b.d) return Integer.compare(a.d, b.d);
            return Integer.compare(a.w, b.w);
        });

        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        long total = 0L;

        for (Box b : boxes) {
            maxHeap.offer(b.w);
            total += b.w;
            if (maxHeap.size() > b.d) {
                total -= maxHeap.poll();
            }
        }

        out.append(maxHeap.size()).append(' ').append(total).append('\n');
        System.out.print(out);
    }
}
