/**
 * Created by David on 28.12.2015.
 */
public class ComplicatedClass {
    public static final double value = 3.14;

    static double variable = 3.13;

    public static class Parent {
        String name;

        public Parent()
        {
            name = "Default constr.";
        }

        public Parent(String name)
        {
            this.name = "Constructed with name: " + name;
        }

        public String getClassName() {
            return "Parent";
        }

        public int getNumber() {
            return 0;
        }

        protected double getDouble() {
            return 3.14;
        }

        private long getLong()
        {
            return 5;
        }

        public int getSuperNumber()
        {
            return 42;
        }
    }

    public static class Child extends Parent {

        public String getClassName() {
            return "Child";
        }

        public int getNumber() {
            return super.getNumber();
        }

        private long getLong() {
            return 20;
        }

        public long getSum()
        {
            return this.getLong() + this.getSuperNumber();
        }
    }

    public static void main()
    {
        double[] doubleArray = new double[10];
        double[][][] multiArray = new double[10][10][10];
        double[][][] unspecifiedMultiArray = new double[10][][];

        Child child = new Child();
        Parent parent = new Child();

        System.out.println(child.getClassName());
        System.out.println(child.getNumber());
        System.out.println(child.getDouble());
        System.out.println(child.getLong());
        System.out.println(child.getSuperNumber());

        System.out.println(parent.getClassName());
        System.out.println(parent.getNumber());
        System.out.println(parent.getDouble());
        System.out.println(parent.getLong());
        System.out.println(child.getSuperNumber());
    }

    public static void main(String[] args) {
        System.out.println("This is main");

        String buildedString = "Ahoj" + "Javo";

        if (true) {
            buildedString = buildedString + " World";
        } else {
            buildedString = " :)";
        }

        int length = "ThisIsLongString".length();

        String upperCase = "ThisStringToUpperCase".toUpperCase();

        Class aClass = "".getClass();

        String string2  = new String(" ahoj ");

        double[] arr = new double[10];
        arr.clone();

        try {
            System.out.println("WOW");
            throw new Exception();
        } catch (Exception e) {
            System.err.println(e.toString());
        }
    }
}
