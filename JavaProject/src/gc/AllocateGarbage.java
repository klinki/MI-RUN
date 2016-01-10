package gc;

/**
 * Created by David on 29.12.2015.
 */
public class AllocateGarbage
{
    public static void main(String[] args) {
        System.out.println("Im going to allocate garbage");

        for (int i = 0; i < 10_000; i++) {
            double[] garbage = new double[100];
            garbage = new double[100];
        }

        System.out.println("I allocated ton of garbage and survived");
    }
}
