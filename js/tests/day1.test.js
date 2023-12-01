import { describe, it, expect } from "vitest";
import { p1, p2 } from "../src/day1.js";

describe("day1 part 1", () => {
    it("works", () => {
        let input = `1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet`;
        let res = p1(input);
        expect(res).toBe(142);
    })
    it("works", () => {
        let input = `two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen`;
        let res = p2(input);
        expect(res).toBe(281);
    })
});
