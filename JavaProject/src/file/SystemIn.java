package file;

import java.util.Scanner;

public class SystemIn
{
    public static void main(String[] args) throws Exception {
        System.out.println("Echo service - testing reading from standard input");

        Scanner scn = new Scanner(System.in);

        System.out.println("Insert number of reads: ");
        int countValues = scn.nextInt();

        for (int i = 0; i < countValues; i++) {
            System.out.print("Insert value: ");
            int value = scn.nextInt();

            System.out.print("Value is: ");
            System.out.print(value);
            System.out.println();
        }

        System.out.println("Finished");
    }
}
