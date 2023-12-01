import { read } from "./reader.js";

const numCodes = {
    zero: 48,
    nine: 57,
};

/**
 * @param {string} input
 * @returns {number} result
 */
export function p1(input) {
    let lines = input.split('\n').filter((line) => line != '');
    let res = 0;
    /** @type {number} */
    let i;
    for (i = 0; i < lines.length; ++i) {
        let line = lines[i];
        /** @type {number} */
        let j;
        let state = "";
        for (j = 0; j < line.length; ++j) {
            let ch = line[j];
            if (numCodes.zero <= ch.charCodeAt(0) && ch.charCodeAt(0) <= numCodes.nine) {
                state += ch;
                break;
            }
        }
        for (j = line.length - 1; j >= 0; j--) {
            let ch = line[j];
            if (numCodes.zero <= ch.charCodeAt(0) && ch.charCodeAt(0) <= numCodes.nine) {
                state += ch;
                break;
            }
        }
        let num = parseInt(state);
        res += num;
    }
    return res;
}

const lookups = [
    { str: "one", num: 1 },
    { str: "two", num: 2 },
    { str: "three", num: 3 },
    { str: "four", num: 4 },
    { str: "five", num: 5 },
    { str: "six", num: 6 },
    { str: "seven", num: 7 },
    { str: "eight", num: 8 },
    { str: "nine", num: 9 },
];

/**
 * @param {string} str
 * @returns {number} lookup num
 */
function lookup(str) {
    /** @type number */
    let i;
    for (i = 0; i < lookups.length; ++i) {
        let lookup = lookups[i];
        if (str.startsWith(lookup.str)) {
            return lookup.num;
        }
    }
    return -1;
}

/**
 * @param {string} input
 * @returns {number} result
 */
export function p2(input) {
    let lines = input.split('\n').filter((line) => line != '');
    let res = 0;
    /** @type {number} */
    let i;
    for (i = 0; i < lines.length; ++i) {
        let line = lines[i];
        /** @type {number} */
        let j;

        let num1 = -1;
        let num2 = -1;
        for (j = 0; j < line.length; ++j) {
            let sub = line.substring(j);
            let numFromSub = lookup(sub);
            if (numFromSub === -1) {
                let ch = line[j];
                if (numCodes.zero <= ch.charCodeAt(0) && ch.charCodeAt(0) <= numCodes.nine) {
                    if (num1 == -1) {
                        num1 = ch.charCodeAt(0) - 48;
                    }
                    num2 = ch.charCodeAt(0) - 48;
                }
            } else {
                if (num1 == -1) {
                    num1 = numFromSub;
                }
                num2 = numFromSub;
            }
        }
        let num = (num1 * 10) + num2;
        res += num;
    }
    return res;
}

async function main() {
    let input = await read(null);
    let res = p2(input);
    console.log({ res });
}

main();

