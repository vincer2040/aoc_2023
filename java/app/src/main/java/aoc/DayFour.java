package aoc;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class DayFour {
    private String input;

    public DayFour(String input) {
        this.input = input;
    }

    public int p1() {
        int res = 0;
        Scanner scanner = new Scanner(this.input);
        while (scanner.hasNextLine()) {
            int cur = 0;
            String line = scanner.nextLine();
            String game = line.split(": ")[1];
            String[] gameSplit = game.split(" \\| ");
            Integer[] winStr = Arrays.stream(gameSplit[0].split(" "))
                    .filter(s -> s != "")
                    .map(s -> Integer.parseInt(s))
                    .toArray(Integer[]::new);
            Integer[] gotStr = Arrays.stream(gameSplit[1].split(" "))
                    .filter(s -> s != "")
                    .map(s -> Integer.parseInt(s))
                    .toArray(Integer[]::new);
            List<Integer> lGotStr = Arrays.asList(gotStr);
            for (Integer w : winStr) {
                if (lGotStr.contains(w)) {
                    cur++;
                }
            }

            if (cur > 0) {
                res += Math.pow(2, (cur - 1));
            }
        }
        scanner.close();
        return res;
    }

    public int p2() {
        int res = 0;
        Scanner scanner = new Scanner(this.input);
        int numLines = this.input.split("\\r?\\n").length;
        ArrayList<Integer> played = new ArrayList<>(numLines);
        for (int i = 0; i < numLines; ++i) {
            played.add(0);
        }
        int lineNum = 0;
        while (scanner.hasNextLine()) {
            int curP = played.get(lineNum);
            played.set(lineNum, curP + 1);
            int cur = 0;
            String line = scanner.nextLine();
            String game = line.split(": ")[1];
            String[] gameSplit = game.split(" \\| ");
            Integer[] winStr = Arrays.stream(gameSplit[0].split(" "))
                    .filter(s -> s != "")
                    .map(s -> Integer.parseInt(s))
                    .toArray(Integer[]::new);
            Integer[] gotStr = Arrays.stream(gameSplit[1].split(" "))
                    .filter(s -> s != "")
                    .map(s -> Integer.parseInt(s))
                    .toArray(Integer[]::new);
            List<Integer> lGotStr = Arrays.asList(gotStr);
            for (Integer w : winStr) {
                if (lGotStr.contains(w)) {
                    cur++;
                }
            }

            for (int w = 0; w < cur; ++w) {
                int old = played.get(w + lineNum + 1);
                played.set(w + lineNum + 1, old + played.get(lineNum));
            }
            lineNum++;
        }

        for (Integer p : played) {
            res += p;
        }
        scanner.close();
        return res;
    }
}
