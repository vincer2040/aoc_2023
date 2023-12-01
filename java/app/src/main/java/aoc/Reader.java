package aoc;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Reader {
    private String path;

    public Reader(String path) {
        this.path = path;
    }

    public String read() throws FileNotFoundException {
        if (this.path != null) {
            return this.readFromFile();
        }
        return this.readFromStdin();
    }

    private String readFromStdin() {
        String res = "";
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            res += line + "\n";
        }

        scanner.close();
        return res;
    }

    private String readFromFile() throws FileNotFoundException {
        String res = "";
        File file = new File(this.path);
        Scanner reader = new Scanner(file);
        while (reader.hasNextLine()) {
            String line = reader.nextLine();
            res += line + "\n";
        }
        reader.close();
        return res;
    }
}
