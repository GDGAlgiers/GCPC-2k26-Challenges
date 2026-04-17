import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        if (!scanner.hasNextInt()) return;
        int n = scanner.nextInt();
        int d = scanner.nextInt();
        
        long[][] dp = new long[1 << n][n];
        for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
        
        int[] adj_mask = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = Math.max(i - d, 0); j < i; j++) {
                adj_mask[i] |= (1 << j);
            }
            for (int j = Math.min(i + d, n - 1); j > i; j--) {
                adj_mask[i] |= (1 << j);
            }
        }
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0 || dp[mask][i] == 0) continue;
                int cur = adj_mask[i] & (~mask);
                while (cur > 0) {
                    int idx = Integer.numberOfTrailingZeros(cur);
                    int next_mask = mask | (1 << idx);
                    dp[next_mask][idx] = (dp[next_mask][idx] + dp[mask][i]);
                    cur ^= (1 << idx);
                }
            }
        }
        
        long ans = 0;
        int full_mask = (1 << n) - 1;
        for (int i = 0; i < n; i++) {
            ans = (ans + dp[full_mask][i]);
        }
        System.out.println(ans);
        scanner.close();
    }
}