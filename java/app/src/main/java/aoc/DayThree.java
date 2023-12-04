package aoc;

import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Map;
import java.util.Objects;
import java.util.Scanner;

public class DayThree {
    private String input;
    private Dir[] dirs;

    public DayThree(String input) {
        this.input = input;
        Dir[] dirs = {
                new Dir(0, -1),
                new Dir(0, 1),
                new Dir(-1, -1),
                new Dir(-1, 0),
                new Dir(-1, 1),
                new Dir(1, -1),
                new Dir(1, 0),
                new Dir(1, 1),
        };
        this.dirs = dirs;
    }

    class Dir {
        public int dy;
        public int dx;

        Dir(int dy, int dx) {
            this.dy = dy;
            this.dx = dx;
        }
    }

    class Position {
        public int y;
        public int x;

        Position(int y, int x) {
            this.y = y;
            this.x = x;
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj) {
                return true;
            }
            if (obj == null || getClass() != obj.getClass()) {
                return false;
            }
            Position pos = (Position) obj;
            return (this.y == pos.y) && (this.x == pos.x);
        }

        @Override
        public int hashCode() {
            return Objects.hash(y, x);
        }
    }

    class Number {
        public int val;
        public ArrayList<Position> positions;

        Number(int val) {
            this.val = val;
            this.positions = null;
        }
    }

    public int p1() {
        int res = 0;
        ArrayList<ArrayList<Character>> matrix = makeMatrix(this.input);
        ArrayList<Number> nums = new ArrayList<>();
        ArrayList<Position> special = new ArrayList<>();
        int i, len = matrix.size();
        for (i = 0; i < len; ++i) {
            ArrayList<Character> row = matrix.get(i);
            int j = 0, row_len = row.size();
            while (j < row_len) {
                Character ch = row.get(j);
                if (Character.isDigit(ch)) {
                    int num_val = 0;
                    ArrayList<Position> positions = new ArrayList<>();
                    while (j < row_len && Character.isDigit(row.get(j))) {
                        num_val = (num_val * 10) + ((int) row.get(j) - (int) '0');
                        Position pos = new Position(i, j);
                        positions.add(pos);
                        j++;
                    }
                    Number num = new Number(num_val);
                    num.positions = positions;
                    nums.add(num);
                    continue;
                }
                if (this.isSpecial(ch)) {
                    Position pos = new Position(i, j);
                    special.add(pos);
                }
                j++;
            }
        }

        for (Number num : nums) {
            for (Position pos : num.positions) {
                boolean found = false;
                for (Dir dir : this.dirs) {
                    int y = pos.y + dir.dy;
                    int x = pos.x + dir.dx;
                    Position check = new Position(y, x);
                    if (special.contains(check)) {
                        found = true;
                        res += num.val;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
        return res;
    }

    public int p2() {
        int res = 0;
        ArrayList<ArrayList<Character>> matrix = makeMatrix(this.input);
        Hashtable<Position, ArrayList<Integer>> map = new Hashtable<>();
        ArrayList<Number> nums = new ArrayList<>();
        ArrayList<Position> gears = new ArrayList<>();
        int i, len = matrix.size();
        for (i = 0; i < len; ++i) {
            ArrayList<Character> row = matrix.get(i);
            int j = 0, row_len = row.size();
            while (j < row_len) {
                Character ch = row.get(j);
                if (Character.isDigit(ch)) {
                    int num_val = 0;
                    ArrayList<Position> positions = new ArrayList<>();
                    while (j < row_len && Character.isDigit(row.get(j))) {
                        num_val = (num_val * 10) + ((int) row.get(j) - (int) '0');
                        Position pos = new Position(i, j);
                        positions.add(pos);
                        j++;
                    }
                    Number num = new Number(num_val);
                    num.positions = positions;
                    nums.add(num);
                    continue;
                }
                if (this.isGear(ch)) {
                    Position pos = new Position(i, j);
                    gears.add(pos);
                }
                j++;
            }
        }

        for (Number num : nums) {
            for (Position pos : num.positions) {
                boolean found = false;
                for (Dir dir : this.dirs) {
                    int y = pos.y + dir.dy;
                    int x = pos.x + dir.dx;
                    Position check = new Position(y, x);
                    if (gears.contains(check)) {
                        found = true;
                        if (!map.containsKey(check)) {
                            ArrayList<Integer> newList = new ArrayList<>();
                            newList.add(num.val);
                            map.put(check, newList);
                        } else {
                            ArrayList<Integer> cur = map.get(check);
                            cur.add(num.val);
                            map.replace(check, cur);
                        }

                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }

        for (Map.Entry<Position, ArrayList<Integer>> entry : map.entrySet()) {
            ArrayList<Integer> val = entry.getValue();
            if (val.size() == 2) {
                Integer a1 = val.get(0);
                Integer a2 = val.get(1);
                res += (a1 * a2);
            }
        }

        return res;

    }

    private ArrayList<ArrayList<Character>> makeMatrix(String input) {
        ArrayList<ArrayList<Character>> res = new ArrayList<>();
        Scanner scanner = new Scanner(input);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            int i, len = line.length();
            ArrayList<Character> row = new ArrayList<>();
            for (i = 0; i < len; ++i) {
                Character ch = line.charAt(i);
                row.add(ch);
            }
            res.add(row);
        }
        scanner.close();
        return res;
    }

    private boolean isSpecial(Character ch) {
        return !Character.isDigit(ch) && ch != '.';
    }

    private boolean isGear(Character ch) {
        return ch == '*';
    }
}
