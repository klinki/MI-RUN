package switches;

/**
 * Created by David on 29.12.2015.
 */
public class HopefullyTableSwitch
{
    public void switchMethod(int a) {
        switch (a) {
            case 0:
                System.out.println("NULA");
                break;
            case 1:
                System.out.println("Tisic");
                break;
            case 2:
                System.out.println("DVA");
                break;
            default:
                System.out.println("Nevim");
                break;
        }
    }

    public static void main(String[] args) {
        HopefullyTableSwitch obj = new HopefullyTableSwitch();

        obj.switchMethod(10);
        obj.switchMethod(0);
        obj.switchMethod(1);
    }
}
