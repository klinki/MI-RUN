package inheritance;

/**
 * Created by David on 30.12.2015.
 */
public class Parent {
    private String myPrivates = "This is exclusivelly private for parent";
    protected String hierarchy = "Protected can be seen by childs";
    public String publicated = "This is extremely publicly exposed";

    protected String gene = "GENE";

    public String greet() {
        return "Hello";
    }

    public String greetMe(String me)
    {
        return this.greet() + " " + me;
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
        return "Father greets!";
    }
}
