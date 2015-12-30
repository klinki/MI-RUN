package inheritance;

import jdk.internal.org.objectweb.asm.tree.ParameterNode;

/**
 * Created by David on 30.12.2015.
 */
public class Child extends Parent
{
    private String myPrivates = "WEEEE, these are CHILDS privates";
    protected String hierarchy = "Protected can be seen by childs";
    public String publicated = "This is extremely publicly exposed";

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

    }
}
