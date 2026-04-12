
// Accepted solution — Java
// Note: DOMjudge requires the public class name to match the filename.
import java.util.*;
import java.io.*;

public class sol {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String rna = br.readLine().trim();

        String[] markers = { "ACGUAUGC", "AUGCGUAG", "UGCUAGCU" };
        for (String m : markers) {
            if (rna.contains(m)) {
                System.out.println("True");
                return;
            }
        }
        System.out.println("False");
    }
}
