import java.io.*;
import java.util.*;

public class sol {
    static final long INF = (long) 4e18;

    static class Edge {
        int to;
        long w;

        Edge(int to, long w) {
            this.to = to;
            this.w = w;
        }
    }

    static class Road {
        int u, v;

        Road(int u, int v) {
            this.u = u;
            this.v = v;
        }
    }

    static class State implements Comparable<State> {
        long dist;
        int node;

        State(long dist, int node) {
            this.dist = dist;
            this.node = node;
        }

        public int compareTo(State other) {
            return Long.compare(this.dist, other.dist);
        }
    }

    static long[] dijkstra(int src, List<Edge>[] graph) {
        int n = graph.length - 1;
        long[] dist = new long[n + 1];
        Arrays.fill(dist, INF);
        dist[src] = 0;

        PriorityQueue<State> pq = new PriorityQueue<>();
        pq.add(new State(0, src));

        while (!pq.isEmpty()) {
            State cur = pq.poll();
            if (cur.dist != dist[cur.node]) {
                continue;
            }
            for (Edge e : graph[cur.node]) {
                long nd = cur.dist + e.w;
                if (nd < dist[e.to]) {
                    dist[e.to] = nd;
                    pq.add(new State(nd, e.to));
                }
            }
        }

        return dist;
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner(System.in);
        int n = fs.nextInt();
        if (n == Integer.MIN_VALUE) {
            return;
        }
        int m = fs.nextInt();

        @SuppressWarnings("unchecked")
        List<Edge>[] graph = new ArrayList[n + 1];
        for (int i = 0; i <= n; i++) {
            graph[i] = new ArrayList<>();
        }

        Road[] roads = new Road[m];
        for (int i = 0; i < m; i++) {
            int u = fs.nextInt();
            int v = fs.nextInt();
            long w = fs.nextLong();
            graph[u].add(new Edge(v, w));
            graph[v].add(new Edge(u, w));
            roads[i] = new Road(u, v);
        }

        long[] distStart = dijkstra(1, graph);
        long[] distEnd = dijkstra(n, graph);

        long ans = distStart[n];
        for (Road road : roads) {
            if (distStart[road.u] < INF / 2 && distEnd[road.v] < INF / 2) {
                ans = Math.min(ans, distStart[road.u] + distEnd[road.v]);
            }
            if (distStart[road.v] < INF / 2 && distEnd[road.u] < INF / 2) {
                ans = Math.min(ans, distStart[road.v] + distEnd[road.u]);
            }
        }

        System.out.println(ans >= INF / 2 ? -1 : ans);
    }

    static class FastScanner {
        private final InputStream in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0;
        private int len = 0;

        FastScanner(InputStream in) {
            this.in = in;
        }

        private int read() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) {
                    return -1;
                }
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);
            if (c == -1) {
                return Integer.MIN_VALUE;
            }
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

        long nextLong() throws IOException {
            int c;
            do {
                c = read();
            } while (c <= ' ' && c != -1);
            int sign = 1;
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
}
