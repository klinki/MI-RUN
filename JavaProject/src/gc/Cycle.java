package gc;

/**
 * Created by David on 31.12.2015.
 */
public class Cycle
{
    protected String name;
    protected Cycle child;
    protected Cycle parent;

    public Cycle(String name)
    {
        this.name = name;
    }

    public Cycle()
    {
        this.child = new Cycle("Son of " + this.name);
        this.child.parent = this;
    }

    public Cycle(Cycle parent)
    {
        this.parent = parent;
    }

    public void familyGreeting()
    {
        System.out.println(this.name);
        this.child.familyGreeting();
    }

    public static void main(String[] args) {
        System.out.println("Allocating cycle");

        Cycle survivingCycle = new Cycle("Surviving cycle");

        for (int i = 0; i < 1000; i++)
        {
            Cycle cycle2 = new Cycle();
        }

        System.out.println("Survived cycle allocation without stack overflow!!!!");

        survivingCycle.familyGreeting();
    }
}
