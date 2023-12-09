package aoc;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;

public class DayNine {
    private String input;

    public DayNine(String input) {
        this.input = input;
    }

    public int p1() {
        int res = 0;
        Scanner scanner = new Scanner(this.input);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            ArrayList<Integer> nums = getNums(line);
            ArrayList<ArrayList<Integer>> difs = getDifs(nums);
            int numToAdd = 0;
            int numToAddTo = nums.get(nums.size() - 1);
            int i = difs.size() - 1;
            for (; i != -1; i--) {
                ArrayList<Integer> curDifs = difs.get(i);
                numToAdd += curDifs.get(curDifs.size() - 1);
            }
            res += numToAddTo + numToAdd;
        }
        scanner.close();
        return res;
    }

    public int p2() {
        int res = 0;
        Scanner scanner = new Scanner(this.input);
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            ArrayList<Integer> nums = getNums(line);
            ArrayList<ArrayList<Integer>> difs = getDifs(nums);
            int numToSubtract = 0;
            int numToSubtractFrom = nums.get(0);
            int i = difs.size() - 1;
            for (; i != -1; i--) {
                ArrayList<Integer> curDifs = difs.get(i);
                numToSubtract = curDifs.get(0) - numToSubtract;
            }
            res += (numToSubtractFrom - numToSubtract);
        }
        scanner.close();
        return res;
    }

    private ArrayList<Integer> getNums(String line) {
        ArrayList<Integer> nums = new ArrayList<>();
        String[] split = line.split(" ");
        for (String s : split) {
            nums.add(Integer.parseInt(s));
        }
        return nums;
    }

    private ArrayList<Integer> getDifsOfCur(ArrayList<Integer> nums) {
        ArrayList<Integer> res = new ArrayList<>();
        int i, len = nums.size();
        for (i = 1; i < len; ++i) {
            int cur = nums.get(i);
            int prev = nums.get(i - 1);
            int n = cur - prev;
            res.add(n);
        }
        return res;
    }

    private ArrayList<ArrayList<Integer>> getDifs(ArrayList<Integer> nums) {
        ArrayList<ArrayList<Integer>> difs = new ArrayList<>();
        ArrayList<Integer> curNums = nums;
        while (true) {
            ArrayList<Integer> curDifs = getDifsOfCur(curNums);
            HashSet<Integer> set = new HashSet<>();
            for (int cur : curDifs) {
                set.add(cur);
            }
            difs.add(curDifs);
            curNums = curDifs;
            if (set.size() == 1) {
                break;
            }
        }
        return difs;
    }
}
