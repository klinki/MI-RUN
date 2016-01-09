package knapsack;

public class Item
{
    protected int Weight;
    protected int Value;

    public Item(int weight, int value) {
        this.Weight = weight;
        this.Value = value;
    }

    public int getWeight() {
        return Weight;
    }

    public int getValue() {
        return Value;
    }
}
