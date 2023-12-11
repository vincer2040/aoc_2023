// @ts-check
/// <reference path = "./day11.d.ts" />

/**
 * @param {string} input
 * @returns {number}
 */
export function p1(input) {
    return solve(input, 1);
}

/**
 * @param {string} input
 * @returns {number}
 */
export function p2(input) {
    return solve(input, 1_000_000);
}

/**
 * @param {string} input
 * @param {number} numTimes
 * @returns {number}
 */
function solve(input, numTimes) {
    let res = 0;
    let lines = input.split("\n").filter(a => a);
    let rowExps = rowExpansions(lines);
    let colExps = colExpansions(lines);
    let galaxies = findGalaxies(lines)
        .map(({ y, x }) => {
            let rowExp = rowExps[y];
            let colExp = colExps[x];
            /** @type number */
            let newY;
            /** @type number */
            let newX;
            if (numTimes == 1) {
                newY = y + rowExp;
                newX = x + colExp
            } else {
                newY = y + (rowExp * (numTimes - 1));
                newX = x + (colExp * (numTimes - 1));
            }
            return { y: newY, x: newX, }
        });
    /** @type Map<Point, Point[]> */
    let map = new Map();
    for (let i = 0; i < galaxies.length; ++i) {
        let p = galaxies[i];
        let ps = [];
        for (let x = i + 1; x < galaxies.length; ++x) {
            ps.push(galaxies[x]);
        }
        map.set(p, ps);
    }

    for (let [key, value] of map) {
        let c = 0;
        for (let val of value) {
            let d = dist(key, val);
            c += d;
        }
        res += c;
    }
    return res;
}

/**
 * @param {string[]} lines
 * @returns {Point[]}
 */
function findGalaxies(lines) {
    let res = [];
    let len = lines.length;
    let rowLen = lines[0].length;
    for (let i = 0; i < len; ++i) {
        let line = lines[i];
        for (let j = 0; j < rowLen; ++j) {
            let ch = line[j];
            if (ch === "#") {
                res.push(createPoint(i, j));
            }
        }
    }
    return res;
}

/**
 * @param {string[]} lines
 * @returns {number[]}
 */
function rowExpansions(lines) {
    let res = [];
    let numExpansions = 0;
    for (let line of lines) {
        /** @type Set<string> */
        let set = new Set();
        line.split('').forEach(x => set.add(x));
        if (set.size === 1) {
            numExpansions++;
        }
        res.push(numExpansions);
    }
    return res;
}

/**
 * @param {string[]} lines
 * @returns {number[]}
 */
function colExpansions(lines) {
    let res = [];
    let len = lines[0].length;
    let numExpansions = 0;
    for (let i = 0; i < len; ++i) {
        /** @type Set<string> */
        let set = new Set();
        lines.forEach(line => set.add(line[i]));
        if (set.size === 1) {
            numExpansions++;
        }
        res.push(numExpansions);
    }
    return res;
}

/**
 * @param {number} y
 * @param {number} x
 * @returns {Point}
 */
function createPoint(y, x) {
    return { y: y, x: x }
}

/**
 * @param {Point} a
 * @param {Point} b
 * @returns {number}
 */
function dist(a, b) {
    let y = Math.abs(a.y - b.y);
    let x = Math.abs(a.x - b.x);
    return y + x;
}
