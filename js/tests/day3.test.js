import { describe, expect, it } from "vitest";
import { p1, p2 } from "../src/day3.js";

describe("part one", () => {
    it("works", () => {
        let input = `467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..`;
        let res = p1(input);
        expect(res).toBe(4361);
    });
});

describe("part two", () => {
    it("works", () => {
        let input = `467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..`;
        let res = p2(input);
        expect(res).toBe(467835);
    });
});
