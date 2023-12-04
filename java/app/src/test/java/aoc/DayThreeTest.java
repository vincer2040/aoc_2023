package aoc;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class DayThreeTest {
    @Test
    void p1Works() throws Exception {
        String input = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
        int res = new DayThree(input).p1();
        assertEquals(4361, res);
    }

    void p2Works() throws Exception {
        String input = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
        int res = new DayThree(input).p2();
        assertEquals(467835, res);
    }
}
