package switches;

/**
 * Created by David on 29.12.2015.
 */
public class HopefullyLookupSwitch
{
    public void switchMethod(int a) {
        switch (a) {
            case 0:
                System.out.println("NULA");
                break;
            case 1000:
                System.out.println("Tisic");
                break;
            default:
                System.out.println("Nevim");
                break;
        }
    }

    public static void main(String[] args) {
        HopefullyLookupSwitch obj = new HopefullyLookupSwitch();

        obj.switchMethod(10);
        obj.switchMethod(0);
        obj.switchMethod(1000);
    }
}
