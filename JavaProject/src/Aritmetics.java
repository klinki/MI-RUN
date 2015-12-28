public class Aritmetics
{
    public double add(double a, double b)
    {
        return a+b;
    }

    public double sub(double a, double b)
    {
        return a-b;
    }

    public double mul(double a, double b)
    {
        return a*b;
    }

    public double div(double a, double b)
    {
        return a/b;
    }

	public static void main(String[] args)
	{
		Aritmetics calc = new Aritmetics();
		double plus = calc.add(1.0, 3.14);
		System.out.println(plus);
	}
}
