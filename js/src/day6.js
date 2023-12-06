// @ts-check

/**
 * @param {string} input
 * @returns {number} result
 */
export function p1(input) {
    let res = 1;
    let split = input.split("\n");
    let times = split[0]
        .replace("Time: ", "")
        .split(" ")
        .filter(s => s.length)
        .map(s => parseInt(s));
    let distances = split[1]
        .replace("Distance: ", "")
        .split(" ")
        .filter(s => s.length)
        .map(s => parseInt(s));
    let len = times.length;
    for (let i = 0; i < len; ++i) {
        let t = times[i];
        let d = distances[i];
        let x = getPossibeWaysToWin(t, d);
        res *= x;
    }
    return res;
}

/**
 * @param {string} input
 * @returns {number} result
 */
export function p2(input) {
    let split = input.split("\n");
    let time = parseInt(
        split[0]
            .replace("Time: ", "")
            .split(" ")
            .filter(s => s.length)
            .reduce((acc, s) => acc + s, ""));
    let distance = parseInt(
        split[1]
            .replace("Distance: ", "")
            .split(" ")
            .filter(s => s.length)
            .reduce((acc, s) => acc + s, ""));
    return getPossibeWaysToWin(time, distance);
}

/**
 * @param {number} time
 * @param {number} dist
 * @returns {number} num ways to win
 */
function getPossibeWaysToWin(time, dist) {
    let d = time * time - 4 * dist;
    let sqrtD = Math.floor(Math.sqrt(d));
    if (sqrtD * sqrtD == d) {
        return sqrtD - 1;
    } else {
        return sqrtD + 1 - ((time & 1) ^ (sqrtD & 1));
    }
}
