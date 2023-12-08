package aoc;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class DayEight {
    private String input;

    class Node {
        public String left;
        public String right;

        public Node(String left, String right) {
            this.left = left;
            this.right = right;
        }
    }

    public DayEight(String input) {
        this.input = input;
    }

    public int p1() {
        String[] instructionsMap = input.split("\n\n");
        String instructions = instructionsMap[0];
        String map = instructionsMap[1];
        Scanner scanner = new Scanner(map);
        HashMap<String, Node> graph = new HashMap<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] fromTos = line.split(" = ");
            String from = fromTos[0];
            String[] leftRight = fromTos[1].split(", ");
            String left = leftRight[0];
            String right = leftRight[1];
            left = left.replace("(", "");
            right = right.replace(")", "");
            Node n = new Node(left, right);
            graph.put(from, n);
        }
        scanner.close();
        return this.walk(graph, "AAA", instructions);
    }

    public long p2() {
        String[] instructionsMap = input.split("\n\n");
        String instructions = instructionsMap[0];
        String map = instructionsMap[1];
        Scanner scanner = new Scanner(map);
        HashMap<String, Node> graph = new HashMap<>();
        ArrayList<Long> paths = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] fromTos = line.split(" = ");
            String from = fromTos[0];
            String[] leftRight = fromTos[1].split(", ");
            String left = leftRight[0];
            String right = leftRight[1];
            left = left.replace("(", "");
            right = right.replace(")", "");
            Node n = new Node(left, right);
            graph.put(from, n);
        }
        for (HashMap.Entry<String, Node> entry : graph.entrySet()) {
            String key = entry.getKey();
            if (!key.endsWith("A")) {
                continue;
            }
            long p = this.walk2(graph, key, instructions);
            paths.add(p);
        }
        scanner.close();
        return lcmOfArr(paths);
    }

    private int walk(HashMap<String, Node> graph, String curLocation, String instructions) {
        int numSteps = 0;
        int instructionIdx = 0;
        while (curLocation.compareTo("ZZZ") != 0) {
            char instruction = instructions.charAt(instructionIdx % instructions.length());
            Node n = graph.get(curLocation);
            if (instruction == 'L') {
                curLocation = n.left;
            } else {
                curLocation = n.right;
            }
            instructionIdx++;
            numSteps++;
        }
        return numSteps;
    }

    private long walk2(HashMap<String, Node> graph, String curLocation, String instructions) {
        long numSteps = 0;
        int instructionIdx = 0;
        while (!curLocation.endsWith("Z")) {
            char instruction = instructions.charAt(instructionIdx % instructions.length());
            Node n = graph.get(curLocation);
            if (instruction == 'L') {
                curLocation = n.left;
            } else {
                curLocation = n.right;
            }
            numSteps++;
            instructionIdx++;
        }
        return numSteps;
    }

    private long gcd(long a, long b) {
        if (b == 0) {
            return a;
        } else {
            return gcd(b, a % b);
        }
    }

    private long lcm(long a, long b) {
        return (a * b) / gcd(a, b);
    }

    private long lcmOfArr(ArrayList<Long> arr) {
        long result = arr.get(0);
        int i;
        for (i = 0; i < arr.size(); ++i) {
            result = lcm(result, arr.get(i));
        }
        return result;
    }
}
