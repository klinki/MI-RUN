package exceptions;

/**
 * Created by David on 29.12.2015.
 */
public class ExceptionThrower
{
    public void throwException()
    {
        throw new SomethingIsWrongException("Hello");
    }
}
