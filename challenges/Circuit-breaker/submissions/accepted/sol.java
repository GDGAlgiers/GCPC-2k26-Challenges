// Accepted solution — Java
import java.io.*;
import java.util.*;

public class sol {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(
            new InputStreamReader(System.in)
        );
        StreamTokenizer st = new StreamTokenizer(br);

        st.nextToken();
        int N = (int) st.nval;
        st.nextToken();
        int W = (int) st.nval;
        st.nextToken();
        int X = (int) st.nval;
        st.nextToken();
        int C = (int) st.nval;
        st.nextToken();
        int E = (int) st.nval;

        List<List<Integer>> failures = new ArrayList<>();
        for (int i = 0; i < N; i++) failures.add(new ArrayList<>());

        for (int i = 0; i < E; i++) {
            st.nextToken();
            int T = (int) st.nval;
            st.nextToken();
            int S = (int) st.nval;
            st.nextToken();
            int R = (int) st.nval;
            if (R == 0) failures.get(S).add(T);
        }

        List<List<int[]>> intervals = new ArrayList<>();
        for (int i = 0; i < N; i++) intervals.add(new ArrayList<>());

        for (int s = 0; s < N; s++) {
            List<Integer> fl = failures.get(s);
            int skipUntil = -1;
            ArrayDeque<Integer> valid = new ArrayDeque<>();

            for (int t : fl) {
                if (t < skipUntil) continue;
                valid.addLast(t);
                while (
                    !valid.isEmpty() && valid.peekFirst() < t - W
                ) valid.pollFirst();
                if (valid.size() == X) {
                    int openTime = t;
                    int closeTime = openTime + C;
                    intervals.get(s).add(new int[] { openTime, closeTime });
                    skipUntil = closeTime;
                    valid.clear();
                }
            }
        }

        st.nextToken();
        int Q = (int) st.nval;
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < Q; i++) {
            st.nextToken();
            int T = (int) st.nval;
            st.nextToken();
            int S = (int) st.nval;
            List<int[]> ivs = intervals.get(S);
            int lo = 0,
                hi = ivs.size() - 1;
            boolean found = false;
            while (lo <= hi) {
                int mid = (lo + hi) >>> 1;
                if (ivs.get(mid)[0] <= T) {
                    if (ivs.get(mid)[1] > T) {
                        found = true;
                        break;
                    }
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            sb.append(found ? "OPEN" : "CLOSED").append('\n');
        }

        System.out.print(sb);
    }
}
