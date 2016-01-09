package file;

import java.io.FileInputStream;
import java.util.Scanner;

public class FileInput
{
    public static void main(String[] args) throws Exception {
        System.out.println("Testing reading from file");

        FileInputStream fileInputStream = new FileInputStream("test.txt");
        Scanner scn = new Scanner(fileInputStream);

        int countValues = scn.nextInt();

        System.out.print("I will try to read  ");
        System.out.print(countValues);
        System.out.println(" values from file");

        for (int i = 0; i < countValues; i++) {
            int value = scn.nextInt();

            System.out.print(value);
            System.out.println();
        }

        System.out.println("Finished");
    }
}
