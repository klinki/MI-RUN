package exceptions;

/**
 * Created by David on 29.12.2015.
 */
public class SomethingIsWrongException extends RuntimeException
{
    SomethingIsWrongException(String str)
    {
        super(str);
    }

    SomethingIsWrongException(String str, Throwable cause)
    {
        super(str, cause);
    }
}
