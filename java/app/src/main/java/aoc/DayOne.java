package aoc;

import java.util.Scanner;

public class DayOne {
    private String input;

    class LookupTable {
        private LookupItem[] lookup;
        private int len;

        class LookupItem {
            public String str;
            public int num;

            public LookupItem(String str, int num) {
                this.str = str;
                this.num = num;
            }
        }

        public LookupTable() {
            LookupItem[] items = {
                    new LookupItem("one", 1),
                    new LookupItem("two", 2),
                    new LookupItem("three", 3),
                    new LookupItem("four", 4),
                    new LookupItem("five", 5),
                    new LookupItem("six", 6),
                    new LookupItem("seven", 7),
                    new LookupItem("eight", 8),
                    new LookupItem("nine", 9),
            };
            this.lookup = items;
            this.len = 9;
        }

        public int lookupInt(String str) {
            int i;
            for (i = 0; i < this.len; ++i) {
                LookupItem item = this.lookup[i];
                if (str.startsWith(item.str)) {
                    return item.num;
                }
            }
            return -1;
        }
    }

    public DayOne(String input) {
        this.input = input;
    }

    public int p1() {
        Scanner scanner = new Scanner(this.input);
        int res = 0;
        while (scanner.hasNextLine()) {
            int num1 = -1;
            int num2 = -1;
            String line = scanner.nextLine();
            int len = line.length();
            int i;
            for (i = 0; i < len; ++i) {
                char ch = line.charAt(i);
                if (Character.isDigit(ch)) {
                    if (num1 == -1) {
                        num1 = ch - '0';
                    }
                    num2 = ch - '0';
                }
            }
            int num = (num1 * 10) + num2;
            res += num;
        }
        scanner.close();
        return res;
    }

    public int p2() {
        Scanner scanner = new Scanner(this.input);
        int res = 0;
        while (scanner.hasNextLine()) {
            int num1 = -1;
            int num2 = -1;
            String line = scanner.nextLine();
            int len = line.length();
            int i;
            LookupTable table = new LookupTable();
            for (i = 0; i < len; ++i) {
                String sub = line.substring(i);
                int lookupInt = table.lookupInt(sub);
                if (lookupInt != -1) {
                    if (num1 == -1) {
                        num1 = lookupInt;
                    }
                    num2 = lookupInt;
                } else {
                    char ch = line.charAt(i);
                    if (Character.isDigit(ch)) {
                        if (num1 == -1) {
                            num1 = ch - '0';
                        }
                        num2 = ch - '0';
                    }
                }
            }
            int num = (num1 * 10) + num2;
            res += num;
        }
        scanner.close();
        return res;
    }
}
