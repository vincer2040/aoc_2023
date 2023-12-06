package aoc;

import java.util.Arrays;

public class DaySix {
    private String input;

    public DaySix(String input) {
        this.input = input;
    }

    public int p1() {
        int res = 1;
        String[] split = input.split("\n");
        Long[] times = Arrays.stream(split[0].replace("Time: ", "").split(" "))
                .filter(s -> s != "")
                .map(s -> Long.parseLong(s))
                .toArray(Long[]::new);
        Long[] distances = Arrays.stream(split[1].replace("Distance: ", "").split(" "))
                .filter(s -> s != "")
                .map(s -> Long.parseLong(s))
                .toArray(Long[]::new);
        int i, len = times.length;
        for (i = 0; i < len; ++i) {
            Long time = times[i];
            Long dist = distances[i];
            System.out.println("time: " + time + " dist: " + dist);
            res *= getPossibleWaysToWin(time, dist);
        }
        return res;
    }

    public Long p2() {
        String[] split = input.split("\n");
        Long time = Long.parseLong(Arrays.stream(split[0].replace("Time: ", "").split(" "))
                .filter(s -> s != "")
                .reduce("", (acc, s) -> acc + s));
        Long distance = Long.parseLong(Arrays.stream(split[1].replace("Distance: ", "").split(" "))
                .filter(s -> s != "")
                .reduce("", (acc, s) -> acc + s));
        return getPossibleWaysToWin(time, distance);
    }

    private Long getPossibleWaysToWin(Long time, Long dist) {
        Long d = time * time - 4 * dist;
        Long sqrtD = (long) Math.sqrt(d);
        if (sqrtD * sqrtD == d) {
            return sqrtD - 1;
        } else {
            return sqrtD + 1 - ((time & 1) ^ (sqrtD & 1));
        }
    }
}
