package loops;

/**
 * Created by David on 10.01.2016.
 */
public class HugeLoops
{
    public void doNothing(int size)
    {
        System.out.println("Beginning empty do-while loop");
        int i = 0;
        do
        {
            i++;
        } while (i < size);
        System.out.println(i);
        System.out.println("End of empty loop");
    }

    public void forDoNothing(int size)
    {
        System.out.println("Beginning empty for loop");
        int i;
        for (i = 0; i < size; i++)
        {
        }
        System.out.println(i);
        System.out.println("End of empty loop");
    }

    public void whileDoNothig(int size)
    {
        System.out.println("Beginning empty while loop");
        int i = 0;
        while (i < size)
        {
            i++;
        }
        System.out.println(i);
        System.out.println("End of empty loop");
    }



    public static void main(String[] args)
    {
        HugeLoops looper = new HugeLoops();

        int array[] = {1000, 10_000, 100_000, 1_000_000};


        for (int size : array) {
            System.out.println("Test with: ");
            System.out.println(size);
            looper.forDoNothing(size);
            looper.doNothing(size);
            looper.whileDoNothig(size);
        }
    }
}
