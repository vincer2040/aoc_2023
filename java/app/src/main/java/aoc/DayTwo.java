package aoc;

import java.util.ArrayList;
import java.util.Scanner;

public class DayTwo {
    private String input;

    private enum Color {
        Red,
        Green,
        Blue,
    }

    class Cube {
        public Color color;
        public int num;

        public Cube(Color color, int num) {
            this.color = color;
            this.num = num;
        }

        public void print() {
            switch (this.color) {
                case Blue:
                    System.out.println("blue: " + this.num);
                    break;
                case Green:
                    System.out.println("green: " + this.num);
                    break;
                case Red:
                    System.out.println("red: " + this.num);
                    break;
            }
        }

        public boolean isPossible() {
            switch (this.color) {
                case Blue:
                    return this.num <= 14;
                case Green:
                    return this.num <= 13;
                case Red:
                    return this.num <= 12;
            }
            return false;
        }
    }

    public DayTwo(String input) {
        this.input = input;
    }

    public int p1() throws Exception {
        Scanner scanner = new Scanner(this.input);
        int res = 0;
        while (scanner.hasNextLine()) {
            boolean possible = true;
            String line = scanner.nextLine();
            String[] split = line.split(": ");
            int id = Integer.parseInt(split[0].split(" ")[1]);
            String gameStr = split[1];
            String[] pullsStr = gameStr.split("; ");
            ArrayList<ArrayList<Cube>> game = new ArrayList<>();
            for (String pullStr : pullsStr) {
                ArrayList<Cube> pulls = new ArrayList<>();
                String[] cubeStrs = pullStr.split(", ");
                for (String cubeStr : cubeStrs) {
                    String[] cubeStrSplit = cubeStr.split(" ");
                    int num = Integer.parseInt(cubeStrSplit[0]);
                    String colorStr = cubeStrSplit[1];
                    Color color = color(colorStr);
                    Cube cube = new Cube(color, num);
                    pulls.add(cube);
                }
                game.add(pulls);
            }
            for (ArrayList<Cube> pull : game) {
                for (Cube cube : pull) {
                    if (!cube.isPossible()) {
                        possible = false;
                    }
                }
            }
            if (possible) {
                res += id;
            }
        }
        scanner.close();
        return res;
    }

    public int p2() throws Exception {
        Scanner scanner = new Scanner(this.input);
        int res = 0;
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] split = line.split(": ");
            String gameStr = split[1];
            String[] pullsStr = gameStr.split("; ");
            ArrayList<ArrayList<Cube>> game = new ArrayList<>();
            for (String pullStr : pullsStr) {
                ArrayList<Cube> pulls = new ArrayList<>();
                String[] cubeStrs = pullStr.split(", ");
                for (String cubeStr : cubeStrs) {
                    String[] cubeStrSplit = cubeStr.split(" ");
                    int num = Integer.parseInt(cubeStrSplit[0]);
                    String colorStr = cubeStrSplit[1];
                    Color color = color(colorStr);
                    Cube cube = new Cube(color, num);
                    pulls.add(cube);
                }
                game.add(pulls);
            }
            int green_amt = 0;
            int blue_amt = 0;
            int red_amt = 0;
            for (ArrayList<Cube> pull : game) {
                for (Cube cube : pull) {
                    switch (cube.color) {
                        case Blue:
                            if (cube.num > blue_amt) {
                                blue_amt = cube.num;
                            }
                            break;
                        case Green:
                            if (cube.num > green_amt) {
                                green_amt = cube.num;
                            }
                            break;
                        case Red:
                            if (cube.num > red_amt) {
                                red_amt = cube.num;
                            }
                            break;
                    }
                }
            }

            int full = green_amt * blue_amt * red_amt;
            res += full;
        }
        scanner.close();
        return res;
    }

    private Color color(String colorStr) throws Exception {
        switch (colorStr) {
            case "red":
                return Color.Red;
            case "blue":
                return Color.Blue;
            case "green":
                return Color.Green;
        }

        throw new Exception("invalid color");
    }
}
