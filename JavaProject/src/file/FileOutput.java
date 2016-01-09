package file;

import java.io.FileOutputStream;
import java.io.PrintStream;

public class FileOutput
{
    public static void main(String[] args) {
        int index = 100;
        try {
            PrintStream printStream = new PrintStream(new FileOutputStream("test.txt"));
            do {
                printStream.println("IM IN THE LOOP");
            } while (index-- > 0);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
