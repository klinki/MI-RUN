package string;

/**
 * Created by David on 29.12.2015.
 */
public class StrBuilder
{
    public static void main(String[] args) {
        String test = "HELLO ";

        for (int i = 0; i < 100; i++) {
            test = test + " HELLO";
        }

        System.out.println(test);
    }
}
