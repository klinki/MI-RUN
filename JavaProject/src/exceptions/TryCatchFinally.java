package exceptions;

/**
 * Created by David on 29.12.2015.
 */
public class TryCatchFinally
{
    public static void main(String[] args) {
        ExceptionThrower second = new ExceptionThrower();
        try {
            System.out.println("This is inside try");
            second.throwException();
        } catch (RuntimeException e) {
            System.out.println("This is inside catch!");
        } finally {
            System.out.println("This is inside finally");
        }
    }
}
