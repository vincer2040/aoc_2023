package aoc;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class DayEleven {
    private ArrayList<String> lines;

    class Point {
        int y;
        int x;

        public Point(int y, int x) {
            this.y = y;
            this.x = x;
        }

        public void print() {
            System.out.println(this.y + " " + this.x);
        }
    }

    public DayEleven(String input) {
        Scanner scanner = new Scanner(input);
        ArrayList<String> ls = new ArrayList<>();
        while (scanner.hasNextLine()) {
            ls.add(scanner.nextLine());
        }
        scanner.close();
        this.lines = ls;
    }

    public long p1() {
        return solve(1);
    }

    public long p2() {
        return solve(1_000_000);
    }

    private long solve(int numTimes) {
        long res = 0;
        ArrayList<Integer> rowExps = rowExpansions();
        ArrayList<Integer> colExps = colExpansions();
        ArrayList<Point> galaxyCoords = new ArrayList<>();
        for (Point p : findGalaxies()) {
            int rowExp = rowExps.get(p.y);
            int colExp = colExps.get(p.x);
            int newY;
            int newX;
            if (numTimes == 1) {
                newY = p.y + rowExp;
                newX = p.x + colExp;
            } else {
                newY = p.y + (rowExp * (numTimes - 1));
                newX = p.x + (colExp * (numTimes - 1));
            }
            Point newP = new Point(newY, newX);
            galaxyCoords.add(newP);
        }
        HashMap<Point, ArrayList<Point>> map = new HashMap<>();
        int i, len = galaxyCoords.size();
        for (i = 0; i < len; ++i) {
            Point point = galaxyCoords.get(i);
            ArrayList<Integer> l = createList(i, len);
            ArrayList<Point> toPoints = new ArrayList<>();
            for (int j : l) {
                Point p = galaxyCoords.get(j);
                toPoints.add(p);
            }
            map.put(point, toPoints);
        }
        for (HashMap.Entry<Point, ArrayList<Point>> e : map.entrySet()) {
            Point point = e.getKey();
            ArrayList<Point> toPoints = e.getValue();
            long c = 0;
            for (Point tp : toPoints) {
                long d = dist(point, tp);
                c += d;
            }
            res += c;
        }
        return res;
    }

    private ArrayList<Integer> createList(int i, int galaxyCoordsLen) {
        ArrayList<Integer> res = new ArrayList<>();
        int len = galaxyCoordsLen - i - 1;
        int x;
        for (x = 0; x < len; ++x) {
            int t = x + i + 1;
            res.add(t);
        }
        return res;
    }

    private ArrayList<Integer> rowExpansions() {
        ArrayList<Integer> res = new ArrayList<>();
        int numExpansions = 0;
        for (String line : this.lines) {
            HashSet<Character> set = new HashSet<>();
            char[] chars = line.toCharArray();
            for (char ch : chars) {
                set.add(ch);
            }

            if (set.size() == 1) {
                numExpansions++;
            }

            res.add(numExpansions);
        }
        return res;
    }

    private ArrayList<Integer> colExpansions() {
        ArrayList<Integer> res = new ArrayList<>();
        int numExpansions = 0;
        int len = this.lines.get(0).length();
        int idx = 0;
        while (idx < len) {
            HashSet<Character> set = new HashSet<>();
            for (String line : this.lines) {
                char ch = line.charAt(idx);
                set.add(ch);
            }
            if (set.size() == 1) {
                numExpansions++;
            }
            res.add(numExpansions);
            idx++;
        }
        return res;
    }

    private ArrayList<Point> findGalaxies() {
        ArrayList<Point> res = new ArrayList<>();
        int i, num_lines = this.lines.size();
        int j, row_len = this.lines.get(0).length();
        for (i = 0; i < num_lines; ++i) {
            for (j = 0; j < row_len; ++j) {
                char ch = this.lines.get(i).charAt(j);
                if (ch == '#') {
                    Point p = new Point(i, j);
                    res.add(p);
                }
            }
        }
        return res;
    }

    private long dist(Point a, Point b) {
        int y = Math.abs(a.y - b.y);
        int x = Math.abs(a.x - b.x);
        return y + x;
    }
}
