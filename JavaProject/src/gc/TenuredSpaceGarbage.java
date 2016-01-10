package gc;

/**
 * Created by David on 10.01.2016.
 */
public class TenuredSpaceGarbage
{
    public static void main(String[] args) {
        System.out.println("Im going to allocate garbage on tenured (perm) space");

        for (int i = 0; i < 10_000; i++) {
            double[] garbage = new double[1000];
            garbage = new double[1000];
        }

        System.out.println("I allocated ton of garbage and survived");
    }
}
