import java.util.*;
import java.io.*;

class sol {
    static final int N = 2005;
    static final long OO = 2_000_000_000_000_000_000L;
    static final long MOD = 998244353;
    
    static byte[][] inGrid = new byte[N][N];
    static byte[][] addGrid = new byte[N][N];
    static long[][] dist = new long[N][N];
    static int[] window = new int[N];
    
    static int[] dx = {1, -1, 0, 0};
    static int[] dy = {0, 0, 1, -1};

    public static void main(String[] args) throws IOException {
        FastReader sc = new FastReader(System.in);
        int n = sc.nextInt();
        int[][] p = new int[n + 1][2];
        
        for (int i = 0; i < n; i++) {
            p[i][0] = sc.nextInt();
            p[i][1] = sc.nextInt();
        }
        p[n] = p[0];

        for (int i = 1; i <= n; i++) {
            int x = p[i][0], y = p[i][1];
            int px = p[i-1][0], py = p[i-1][1];
            
            for (int j = Math.min(py, y); j <= Math.max(py, y); j++) inGrid[x][j] = 1;
            for (int j = Math.min(px, x); j <= Math.max(px, x); j++) inGrid[j][y] = 1;
            for (int j = Math.min(py, y); j < Math.max(py, y); j++)  addGrid[x][j] = 1;
        }

        List<int[]> sources = new ArrayList<>();
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                if (inGrid[x][y] == 1) sources.add(new int[]{x, y});
                inGrid[x][y] |= (byte)(window[y] & 1);
                window[y] += addGrid[x][y];
            }
        }

        // 3. BFS
        for (int i = 0; i < N; i++) Arrays.fill(dist[i], OO);
        Deque<int[]> q = new ArrayDeque<>(sources);
        for (int[] s : sources) dist[s[0]][s[1]] = 0;

        while (!q.isEmpty()) {
            int[] curr = q.poll();
            int x = curr[0], y = curr[1];
            
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                    if (dist[nx][ny] == OO && inGrid[nx][ny] == 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.add(new int[]{nx, ny});
                    }
                }
            }
        }

        // 4. Result
        List<Long> vals = new ArrayList<>();
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                if (inGrid[x][y] == 1) vals.add(dist[x][y]);
            }
        }
        Collections.sort(vals);

        long ans = 0, pw = 1;
        for (long v : vals) {
            ans = (ans + (v % MOD) * pw) % MOD;
            pw = (pw * 2) % MOD;
        }

        long inv = power((pw - 1 + MOD) % MOD, MOD - 2);
        System.out.println((ans * inv) % MOD);
    }

    static long power(long a, long b) {
        long res = 1;
        a %= MOD;
        while (b > 0) {
            if ((b & 1) == 1) res = (res * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }

    static class FastReader {
        private BufferedReader reader;
        private StringTokenizer tokenizer;

        public FastReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream));
        }

        public String next() throws IOException {
            while (tokenizer == null || !tokenizer.hasMoreElements()) {
                tokenizer = new StringTokenizer(reader.readLine());
            }
            return tokenizer.nextToken();
        }

        public int nextInt() throws IOException { return Integer.parseInt(next()); }
    }
}