// @ts-check
/// reference types ./day3.d.ts

const nums = {
    zero: 48,
    nine: 57,
};

/** @type Dir[] */
const dirs = [
    { dy: 0, dx: -1 },
    { dy: 0, dx: 1 },
    { dy: -1, dx: -1 },
    { dy: -1, dx: 0 },
    { dy: -1, dx: 1 },
    { dy: 1, dx: -1 },
    { dy: 1, dx: 0 },
    { dy: 1, dx: 1 },
];

/**
 * @param {string} input
 * @returns {number} res
 */
export function p1(input) {
    let res = 0;
    let matrix = makeMatrix(input);

    /** @type number*/
    let i;
    /** @type Num[]*/
    let nums = [];
    /** @type Position[]*/
    let special = [];
    for (i = 0; i < matrix.length; ++i) {
        let row = matrix[i];
        let j = 0;
        let len = row.length;
        while (j < len) {
            let ch = row[j];
            if (isDigit(ch)) {
                let numVal = 0;
                /** @type Position[] */
                let positions = [];
                while (j < len && isDigit(row[j])) {
                    numVal = (numVal * 10) + parseInt(row[j]);
                    /** @type Position */
                    let pos = { y: i, x: j };
                    positions.push(pos);
                    j++;
                }
                /** @type Num */
                let num = { val: numVal, positions };
                nums.push(num);
                continue;
            }
            if (isSpecial(ch)) {
                /** @type Position */
                let pos = { y: i, x: j };
                special.push(pos);
            }
            j++;
        }
    }

    for (let num of nums) {
        next_num:
        for (let pos of num.positions) {
            for (let dir of dirs) {
                /** @type Position */
                let check = { y: pos.y + dir.dy, x: pos.x + dir.dx };
                let found = special.find((s) => {
                    return s.y === check.y && s.x === check.x;
                });
                if (found) {
                    res += num.val;
                    break next_num;
                }
            }
        }
    }
    return res;
}

/**
 * @param {string} input
 * @returns {number} res
 */
export function p2(input) {
    let res = 0;
    let matrix = makeMatrix(input);

    /** @type Map<string, number[]>*/
    let map = new Map();

    /** @type number*/
    let i;
    /** @type Num[]*/
    let nums = [];
    /** @type Position[]*/
    let gears = [];
    for (i = 0; i < matrix.length; ++i) {
        let row = matrix[i];
        let j = 0;
        let len = row.length;
        while (j < len) {
            let ch = row[j];
            if (isDigit(ch)) {
                let numVal = 0;
                /** @type Position[] */
                let positions = [];
                while (j < len && isDigit(row[j])) {
                    numVal = (numVal * 10) + parseInt(row[j]);
                    /** @type Position */
                    let pos = { y: i, x: j };
                    positions.push(pos);
                    j++;
                }
                /** @type Num */
                let num = { val: numVal, positions };
                nums.push(num);
                continue;
            }
            if (isGear(ch)) {
                /** @type Position */
                let pos = { y: i, x: j };
                gears.push(pos);
            }
            j++;
        }
    }

    for (let num of nums) {
        next_num:
        for (let pos of num.positions) {
            for (let dir of dirs) {
                /** @type Position */
                let check = { y: pos.y + dir.dy, x: pos.x + dir.dx };
                let found = gears.find((s) => {
                    return s.y === check.y && s.x === check.x;
                });
                if (found) {
                    let stringCheck = JSON.stringify(check);
                    if (map.has(stringCheck)) {
                        map.get(stringCheck)?.push(num.val);
                    } else {
                        map.set(stringCheck, [num.val]);
                    }
                    break next_num;
                }
            }
        }
    }

    for (let [_, val] of map) {
        if (val.length == 2) {
            res += (val[0] * val[1]);
        }
    }
    return res;
}

/**
 * @param {string} input
 * @returns {Matrix} matrix
 */
function makeMatrix(input) {
    return input.split("\n").filter((line) => line !== "").map((line) => line.split(""));
}

/**
 * @param {string} ch
 * @returns {boolean} is digit
 */
function isDigit(ch) {
    let charCode = ch.charCodeAt(0);
    return nums.zero <= charCode && charCode <= nums.nine;
}

/**
 * @param {string} ch
 * @returns {boolean} is special
 */
function isSpecial(ch) {
    return !isDigit(ch) && ch != ".";
}

/**
 * @param {string} ch
 * @returns {boolean} is special
 */
function isGear(ch) {
    return ch === "*";
}
