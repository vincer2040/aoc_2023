package aoc;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class DayOneTest {
    @Test
    void p1Works() {
        String input = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet";
        int res = new DayOne(input).p1();
        assertEquals(142, res);
    }

    @Test
    void p2Works() {
        String input = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen";
        int res = new DayOne(input).p2();
        assertEquals(281, res);
    }
}
