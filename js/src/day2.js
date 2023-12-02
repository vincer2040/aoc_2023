/// <reference path = "./day2.d.ts" />

/**
 * @param {string} input
 */
export function p1(input) {
    let lines = input.split('\n').filter((line) => line != "");
    let res = 0;
    for (let line of lines) {
        let possible = true;
        let [idStr, pullsStr] = line.split(": ");
        let [_, id] = idStr.split(" ");
        let game = pullsStr.split("; ").map((pullStr) => {
            return pullStr.split(", ").map((p) => {
                let [num, color] = p.split(" ");
                /** @type {Color} */
                let obj = { color: color, num: parseInt(num) };
                return obj;
            });
        });

        for (let g of game) {
            for (let color of g) {
                if (!isPossible(color)) {
                    possible = false;
                }
            }
        }
        if (possible) {
            res += parseInt(id);
        }
    }
    return res;
}

/**
 * @param {string} input
 */
export function p2(input) {
    let lines = input.split('\n').filter((line) => line != "");
    let res = 0;
    for (let line of lines) {
        let [_, pullsStr] = line.split(": ");
        let game = pullsStr.split("; ").map((pullStr) => {
            return pullStr.split(", ").map((p) => {
                let [num, color] = p.split(" ");
                /** @type {Color} */
                let obj = { color: color, num: parseInt(num) };
                return obj;
            });
        });

        let green_amt = 0;
        let blue_amt = 0;
        let red_amt = 0;
        for (let g of game) {
            for (let color of g) {
                if (color.color === "green") {
                    if (green_amt < color.num) {
                        green_amt = color.num;
                    }
                } else if (color.color === "red") {
                    if (red_amt < color.num) {
                        red_amt = color.num;
                    }
                } else if (color.color === "blue") {
                    if (blue_amt < color.num) {
                        blue_amt = color.num;
                    }
                }
            }
        }

        let full = green_amt * blue_amt * red_amt;

        res += full;

    }
    return res;
}

/**
 * @param {Color} color
 * @returns {boolean} is possible
 */
function isPossible(color) {
    if (color.color === "green") {
        if (color.num > 13) {
            return false;
        }
        return true;
    }
    if (color.color === "blue") {
        if (color.num > 14) {
            return false;
        }
        return true;
    }
    if (color.color === "red") {
        if (color.num > 12) {
            return false;
        }
        return true;
    }
    return false;
}
