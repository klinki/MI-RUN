package knapsack;

public class Knapsack
{
    protected int maxWeight;

    protected Item[] availableItems;
    protected Item[] itemsInKnapsack;

    protected Item[] bestSolution;
    protected int bestSolutionWeight;
    protected int bestSolutonValue;

    protected int countOfItems;

    public Knapsack(Item[] availableItems, int maxWeight) {
        this.availableItems = availableItems;
        this.bestSolutonValue = 0;
        this.bestSolutionWeight = 0;
        this.maxWeight = maxWeight;
        this.itemsInKnapsack = new Item[availableItems.length];
        this.bestSolution = new Item[availableItems.length];

        this.countOfItems = 0;
    }

    public int getWeight()
    {
        int weight = 0;
        for (int i = 0; i < this.countOfItems; i++) {
            weight += this.itemsInKnapsack[i].getWeight();
        }

        return weight;
    }

    public int getValue()
    {
        int value = 0;
        for (int i = 0; i < this.countOfItems; i++) {
            value += this.itemsInKnapsack[i].getValue();
        }

        return value;
    }

    protected void copyCurrentSolution()
    {
        for (int i = 0; i < this.availableItems.length; i++) {
            this.bestSolution[i] = this.itemsInKnapsack[i];
        }

        this.bestSolutionWeight = this.getWeight();
        this.bestSolutonValue = this.getValue();
    }

    public void solve()
    {
        this.solve(0, 0, 0);
    }

    public void solve(int level, int value, int weight)
    {
        if (level >= availableItems.length) {
            if (value > this.bestSolutonValue && weight <= this.maxWeight)  {
                this.bestSolutonValue = value;
                this.bestSolutionWeight = weight;
            }

            return;
        }

        if (weight > this.maxWeight) {
            return;
        }

        this.solve(level + 1,
                value + this.availableItems[level].getValue(),
                weight + this.availableItems[level].getWeight()); // item is inside

        this.solve(level + 1,
                value,
                weight
        ); // item is inside
    }

    public static void main(String[] args) {
        // W, C
        int knapsackSize = 100;

        Item[] items = new Item[10];
        items[0] = new Item(27, 38);
        items[1] = new Item(2, 86);
        items[2] = new Item(41, 112);
        items[3] = new Item(1, 0);
        items[4] = new Item(25, 66);
        items[5] = new Item(1, 97);
        items[6] = new Item(34, 195);
        items[7] = new Item(3, 85);
        items[8] = new Item(50, 42);
        items[9] = new Item(12, 223);

        Knapsack solver = new Knapsack(items, knapsackSize);
        solver.solve();

        System.out.println("Best solution is: ");
        System.out.print("Weight: ");
        System.out.println(solver.bestSolutionWeight);
        System.out.print("Value: ");
        System.out.println(solver.bestSolutonValue);

        System.out.print("Correct solution: ");
        System.out.println("798");
    }
}
