import java.util.*;
import java.io.*;

public class sol {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StreamTokenizer st = new StreamTokenizer(br);

        st.nextToken(); int n = (int) st.nval;
        st.nextToken(); int k = (int) st.nval;

        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            st.nextToken();
            a[i] = (int) st.nval;
        }

        List<Integer> vec = new ArrayList<>();
        int ans = 0;
        vec.add(1);

        for (int i = 1; i < n; i++) {
            if (a[i] * 2 > a[i - 1]) {
                vec.set(vec.size() - 1, vec.get(vec.size() - 1) + 1);
            } else {
                vec.add(1);
            }
        }

        for (int x : vec) ans += Math.max(x - k, 0);

        System.out.println(ans);
    }
}
