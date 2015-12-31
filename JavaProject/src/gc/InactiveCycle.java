package gc;

/**
 * Created by David on 31.12.2015.
 */
public class InactiveCycle
{
    protected InactiveCycle child;
    protected InactiveCycle parent;

    public InactiveCycle()
    {
        this.child = new InactiveCycle(this);
    }

    public InactiveCycle(InactiveCycle parent)
    {
        this.parent = parent;
    }

    public static void main(String[] args) {
        System.out.println("Allocating cycle");

        for (int i = 0; i < 100000; i++)
        {
            InactiveCycle cycle2 = new InactiveCycle();
        }

        System.out.println("Survived cycle allocation without stack overflow!!!!");
    }
}
