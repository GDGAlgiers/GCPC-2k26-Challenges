// Accepted solution — Java
import java.io.*;
import java.util.*;

public class sol {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int B = Integer.parseInt(st.nextToken());

        long[] dp = new long[B + 1];
        dp[0] = 1;

        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(br.readLine());
            int k = Integer.parseInt(st.nextToken());
            int[] replicas = new int[k];
            for (int j = 0; j < k; j++) replicas[j] = Integer.parseInt(
                st.nextToken()
            );

            long[] ndp = new long[B + 1];
            for (int latency : replicas)
                for (int b = latency; b <= B; b++) ndp[b] += dp[b - latency];
            dp = ndp;
        }

        long ans = 0;
        for (long v : dp) ans += v;
        System.out.println(ans);
    }
}
