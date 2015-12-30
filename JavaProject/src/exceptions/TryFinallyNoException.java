package exceptions;

/**
 * Created by David on 29.12.2015.
 */
public class TryFinallyNoException
{
    public static void main(String[] args) {
        ExceptionThrower second = new ExceptionThrower();

        try {
            System.out.println("This is inside lonely try");
        } finally {
            System.out.println("Im still waiting for exception");
        }

        System.out.println("Hooraaaaay, no exceptions");
    }
}
