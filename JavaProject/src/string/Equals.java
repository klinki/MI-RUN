package string;

/**
 * Created by David on 10.01.2016.
 */
public class Equals
{
    public static void main(String[] args) {
        String a = "A";
        String b = "A";
        String c = "C";

        if (a == null) {
            System.out.println("A IS NULL");
        }

        if (a != null) {
            System.out.println("A is not null");
        }

        if (a == b) {
            System.out.println("Pointers are equal");
        }

        if (a.equals(b)) {
            System.out.println("Strings are equal");
        }

        if (!a.equals(c)) {
            System.out.println("A AND C ARE NOT EQUAL");
        } else {
            System.out.println("A and C are equal");
        }

        if (a.length() == c.length()) {
            System.out.println("Same lengths");
        }
    }
}
