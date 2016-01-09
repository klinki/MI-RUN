package gc;

/**
 * Created by David on 31.12.2015.
 */
public class Finalization
{
    public void finalize()
    {
        System.out.println("Finalize, please!");
    }

    public static void main(String[] args) {
        System.out.println("Testing finalization");

        for (int i = 0; i < 1000; i++) {
            double[] array = new double[100];
            Finalization finalizable = new Finalization();
        }
    }
}
