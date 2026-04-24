import java.io.*;
import java.util.*;

public class sol {
    public static void main(String[] args) throws IOException {
        FastScanner fs = new FastScanner(System.in);

        int N = fs.nextInt();

        int[][] mat = new int[20][20];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                mat[i][j] = fs.nextInt();
            }
        }

        int best = N;

        for (int mask = 0; mask < (1 << N); mask++) {
            int[] covered = new int[20];
            int count = 0;

            for (int i = 0; i < N; i++) {
                if ((mask & (1 << i)) != 0) {
                    count++;
                    covered[i] = 1;

                    for (int j = 0; j < N; j++) {
                        if (mat[i][j] == 1) {
                            covered[j] = 1;
                        }
                    }
                }
            }

            boolean ok = true;
            for (int i = 0; i < N; i++) {
                if (covered[i] == 0) {
                    ok = false;
                    break;
                }
            }

            if (ok && count < best) {
                best = count;
            }
        }

        System.out.println(best);
    }

    static class FastScanner {
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
}
