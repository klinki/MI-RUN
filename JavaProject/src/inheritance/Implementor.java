package inheritance;

/**
 * Created by David on 03.01.2016.
 */
public class Implementor implements Interface
{
    @Override
    public void execute()
    {
        System.out.println("Implemented interface");
    }

    public static void main(String[] args) {
        Interface iface = new Implementor();
        iface.execute();
    }
}
