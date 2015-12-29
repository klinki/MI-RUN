package exceptions;

/**
 * Created by David on 29.12.2015.
 */
public class All
{
    public static void main(String[] args) {
        ExceptionThrower second = new ExceptionThrower();

        System.out.println("Hello world");

        try {
            second.throwException();
        } catch (RuntimeException e) {
            System.out.println("Gotcha!");
        }

        try {
            System.out.println("This is inside try");
            second.throwException();
        } catch (RuntimeException e) {
            System.out.println("This is inside catch!");
        } finally {
            System.out.println("This is inside finally");
        }

        try {
            System.out.println("This is inside lonely try");
        } finally {
            System.out.println("Boooring, no exception!");
        }

        try {
            System.out.println("This is inside lonely try");
            second.throwException();
        } finally {
            System.out.println("Wow! Did you see that? Exception was falling!");
        }

        System.out.println("OKI, I quit, Just throw stupid exceptioooon");

        second.throwException();
    }
}
