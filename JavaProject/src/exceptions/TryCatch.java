package exceptions;

/**
 * Created by David on 29.12.2015.
 */
public class TryCatch
{
    public static void main(String[] args) {
        ExceptionThrower second = new ExceptionThrower();
        try {
            second.throwException();
        } catch (RuntimeException e) {
            System.out.println("Gotcha!");
        }
    }
}
