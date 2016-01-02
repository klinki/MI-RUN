package errors;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by David on 01.01.2016.
 */
public class ClassNotFound
{
    public static void main(String[] args) {
        System.out.println("This one should throw class not found exception");
        List list = new ArrayList();
    }
}
