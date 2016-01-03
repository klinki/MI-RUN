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
        this.child = new Cycle(this);
    }

    public Cycle()
    {
        this.name = "Empty cycle";
        this.child = new Cycle("Son of " + this.name);
        this.child.parent = this;
    }

    public Cycle(Cycle parent)
    {
        this.name = "Son of " + parent.name;
        this.parent = parent;
    }

    public void familyGreeting()
    {
        System.out.println(this.name);
        if (this.child != null) {
            this.child.familyGreeting();
        }
    }

    public static void main(String[] args) {
        System.out.println("Allocating cycle");

        Cycle survivingCycle = new Cycle("Surviving cycle");

        survivingCycle.familyGreeting();

        for (int i = 0; i < 1000; i++)
        {
            Cycle cycle2 = new Cycle();
        }

        System.out.println("Survived cycle allocation without stack overflow!!!!");

        survivingCycle.familyGreeting();
    }
}
