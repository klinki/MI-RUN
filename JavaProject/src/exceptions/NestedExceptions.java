package exceptions;

/**
 * Created by David on 03.01.2016.
 */
public class NestedExceptions
{
    public void firstLevelException()
    {
        throw new SomethingIsWrongException("First level exception");
    }

    public void secondLevelException()
    {
        try {
            this.firstLevelException();
        } catch (Exception e) {
            throw new SomethingIsWrongException("Second level exception", e);
        }
    }
    public static void main(String[] args)
    {
        NestedExceptions nested = new NestedExceptions();

        try {
            nested.secondLevelException();
        } catch (Exception e) {

            Throwable parent = e.getCause();

            System.out.println("Caught exception");
            System.out.println(e.getMessage());
            System.out.println("Parent message: ");
            System.out.println(parent.getMessage());
            System.out.println("Stack trace: ");
            e.printStackTrace();
            System.out.println("Parent stack trace: ");
            parent.printStackTrace();
        }
    }
}
