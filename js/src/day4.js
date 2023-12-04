// @ts-check

/**
 * @param {string} input
 * @returns {number} result
 */
export function p1(input) {
    let res = 0;
    let lines = input.split('\n').filter(line => line !== "");
    for (let line of lines) {
        let cur = 0;
        let game = line.split(": ")[1].split(" | ");
        let winNums = game[0].split(" ").filter(s => s !== "").map(s => parseInt(s));
        let gotNums = game[1].split(" ").filter(s => s !== "").map(s => parseInt(s));
        for (let num of winNums) {
            if (gotNums.find(n => n === num)) {
                cur++;
            }
        }
        if (cur > 0) {
            res += Math.pow(2, (cur - 1));
        }
    }
    return res;
}

/**
 * @param {string} input
 * @returns {number} result
 */
export function p2(input) {
    let lines = input.split('\n').filter(line => line !== "");
    let played = new Array(lines.length).fill(0);
    for (let [i, line] of lines.entries()) {
        played[i] += 1;
        let cur = 0;
        let game = line.split(": ")[1].split(" | ");
        let winNums = game[0].split(" ").filter(s => s !== "").map(s => parseInt(s));
        let gotNums = game[1].split(" ").filter(s => s !== "").map(s => parseInt(s));
        for (let num of winNums) {
            if (gotNums.find(n => n === num)) {
                cur++;
            }
        }

        for (let j = 0; j < cur; ++j) {
            played[j + i + 1] += played[i];
        }
    }
    return played.reduce((acc, cur) => cur + acc, 0);
}
