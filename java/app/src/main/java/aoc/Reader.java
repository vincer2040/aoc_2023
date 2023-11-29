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
        String res = "";
        File file = new File(this.path);
        Scanner reader = new Scanner(file);
        while (reader.hasNextLine()) {
            String line = reader.nextLine();
            res.concat(line);
        }
        reader.close();
        return res;
    }
}
