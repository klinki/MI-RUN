package inheritance;

/**
 * Created by David on 30.12.2015.
 */
public class Child extends Parent
{
    private String myPrivates = "WEEEE, these are CHILDS privates";
    protected String hierarchy = "Iam child and I see protected (from child)";
    public String publicated = "This is extremely publicly exposed, especially for child";

    public String greet()
    {
        return "Heeey, child";
    }

    public String getMyPrivates()
    {
        return this.myPrivates;
    }

    public String getMyHierarchy()
    {
        return this.hierarchy;
    }

    public String familyGreeting()
    {
        return super.familyGreeting() + " " + " and child as well!";
    }

    public String getMyGene()
    {
        return this.gene;
    }

    public void compare()
    {
        System.out.println("");
        System.out.println("--------------------");
        System.out.println("Lets compare my and my fathers values!");
        System.out.println("My: hierarchy " + this.hierarchy);
        System.out.println("My privates: " + this.myPrivates);
        System.out.println("My publicated: " + this.publicated);
        System.out.println("My gene: " + this.gene);

        System.out.println("");

        System.out.println("Daddys: hierarchy " + super.hierarchy);
        System.out.println("Daddys publicated: " + super.publicated);
        System.out.println("Daddys gene: " + super.gene);
        System.out.println("--------------------");
        System.out.println("");
    }

    public void change()
    {
        this.hierarchy += "OOPS, I changed that!";
        this.myPrivates += "OOPS, I changed that!";
        this.publicated += "OOOPS I changed that!";
        this.gene += "OOOPS, I changed that!";
    }

    public void changeDaddy()
    {
        super.hierarchy += "Sorry daddy, I Guess I shoudln't";
        super.publicated += "Sorry daddy, I Guess I shoudln't";
        super.gene += "Sorry daddy, I Guess I shoudln't";
    }

    public static void main(String[] args) {
        Child child = new Child();
        Parent parent = new Parent();
        Parent childAsParent = new Child();

        System.out.println(child.greet());
        System.out.println(child.getMyPrivates());
        System.out.println(child.getMyHierarchy());
        System.out.println(child.familyGreeting());
        System.out.println(child.getMyGene());
        System.out.println(child.greetMe("David"));

        System.out.println("And what about changing them? It will be fun!");

        child.compare();
        child.change();
        child.compare();
        child.changeDaddy();
        child.compare();

        System.out.println(parent.greet());
        System.out.println(parent.getMyPrivates());
        System.out.println(parent.getMyHierarchy());
        System.out.println(parent.familyGreeting());
//        System.out.println(parent.getMyGene());
        System.out.println(parent.greetMe("David"));

        System.out.println(childAsParent.greet());
        System.out.println(childAsParent.getMyPrivates());
        System.out.println(childAsParent.getMyHierarchy());
        System.out.println(childAsParent.familyGreeting());
//        System.out.println(childAsParent.getMyGene());
        System.out.println(childAsParent.greetMe("David"));

        Child unmasked = (Child)childAsParent;
        unmasked.compare();
        childAsParent.change();
        unmasked.compare();
        unmasked.changeDaddy();
        unmasked.compare();
    }
}
