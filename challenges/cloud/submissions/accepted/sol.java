import java.util.Scanner;

public class sol {
    static long sz(long n, long k) {
        if (k > n) return 0;
        if (n == 1) return 1;
        return (n % 2 == 0) ? 2 * sz(n / 2, k) : 1 + 2 * sz(n / 2, k);
    }

    static long f(long n, long k) {
        if (k > n) return 0;
        if (n == 1) return 1;
        if (n % 2 == 0) return 2 * f(n / 2, k) + (n / 2) * sz(n / 2, k);
        long m = (n + 1) / 2;
        return m + 2 * f(n / 2, k) + m * sz(n / 2, k);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (sc.hasNextLong()) {
            long n = sc.nextLong(), k = sc.nextLong(), N = sc.nextLong(), K = sc.nextLong();
            long r = f(n, k), h = f(N, K);
            if (r > h) System.out.println("Raouf");
            else if (r < h) System.out.println("Hachem");
            else System.out.println("Tie");
        }
    }
}