package gc;

/**
 * Created by David on 31.12.2015.
 */
public class TenuredSpaceAllocation
{
    public void finalize()
    {
        System.out.println("Finalize, please!");
    }

    public static void main(String[] args) {
        System.out.println("Testing tenured space allocation");
        double[] array = new double[1000];

        for (int i = 0; i < 100000; i++) {
            Finalization finalizable = new Finalization();
        }
    }
}
