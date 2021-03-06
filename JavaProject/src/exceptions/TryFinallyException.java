package exceptions;

/**
 * Created by David on 29.12.2015.
 */
public class TryFinallyException
{
    public static void main(String[] args) {
        ExceptionThrower second = new ExceptionThrower();

        try {
            System.out.println("This is inside lonely try");
            second.throwException();
        } finally {
            System.out.println("Wow! Did you see that? Exception was falling!");
        }

        System.out.println("I should not see this, I think");
    }
}
