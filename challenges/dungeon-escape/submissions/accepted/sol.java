import java.util.*;
import java.io.*;

public class sol {
    static class Node {
        int r, c, hasKey, steps;

        Node(int r, int c, int hasKey, int steps) {
            this.r = r;
            this.c = c;
            this.hasKey = hasKey;
            this.steps = steps;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt())
            return;
        int n = sc.nextInt();
        int m = sc.nextInt();

        String[] grid = new String[n];
        int sr = -1, sc_pos = -1, er = -1, ec = -1;

        for (int i = 0; i < n; i++) {
            grid[i] = sc.next();
            for (int j = 0; j < m; j++) {
                char c = grid[i].charAt(j);
                if (c == 'S') {
                    sr = i;
                    sc_pos = j;
                } else if (c == 'E') {
                    er = i;
                    ec = j;
                }
            }
        }

        if (sr == -1 || er == -1) {
            System.out.println("-1");
            return;
        }

        boolean[][][] vis = new boolean[n][m][2];
        Queue<Node> q = new LinkedList<>();

        q.add(new Node(sr, sc_pos, 0, 0));
        vis[sr][sc_pos][0] = true;

        int[] dr = { -1, 1, 0, 0 };
        int[] dc = { 0, 0, -1, 1 };

        while (!q.isEmpty()) {
            Node curr = q.poll();

            if (curr.r == er && curr.c == ec) {
                System.out.println(curr.steps);
                return;
            }

            for (int i = 0; i < 4; i++) {
                int nr = curr.r + dr[i];
                int nc = curr.c + dc[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    char cell = grid[nr].charAt(nc);
                    if (cell == '#')
                        continue;

                    int nKey = curr.hasKey;
                    if (cell == 'k')
                        nKey = 1;
                    else if (cell == 'K' && curr.hasKey == 0)
                        continue;

                    if (!vis[nr][nc][nKey]) {
                        vis[nr][nc][nKey] = true;
                        q.add(new Node(nr, nc, nKey, curr.steps + 1));
                    }
                }
            }
        }

        System.out.println("-1");
    }
}
