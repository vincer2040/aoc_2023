// @ts-check

/**
 * @param {string} input
 * @returns {number}
 */
export function p1(input) {
    let lines = input.split("\n").filter(a => a);
    let res = 0;
    for (let line of lines) {
        let nums = getNums(line);
        let numToAddTo = nums[nums.length - 1];
        let difs = getDifs(nums);
        let numToAdd = 0;
        for (let d of difs) {
            let c = d[d.length - 1];
            numToAdd += c;
        }
        res += numToAddTo + numToAdd;
    }
    return res;
}

/**
 * @param {string} input
 * @returns {number}
 */
export function p2(input) {
    let lines = input.split("\n").filter(a => a);
    let res = 0;
    for (let line of lines) {
        let nums = getNums(line);
        let numToSubtractFrom = nums[0];
        let difs = getDifs(nums);
        let numToSubtract = 0;
        for (let d of difs) {
            let c = d[0];
            numToSubtract = c - numToSubtract;
        }
        res += (numToSubtractFrom - numToSubtract);
    }
    return res;
}

/**
 * @param {string} line
 * @returns {number[]}
 */
function getNums(line) {
    return line.split(" ").map((a) => parseInt(a));
}

/**
 * @param {number[]} nums
 * @returns {number[][]}
 */
function getDifs(nums) {
    let res = [];
    let curNums = nums;

    /**
     * @param {number[]} curNums
     * @returns {number[]}
     */
    function getCurDifs(curNums) {
        let res = [];
        for (let i = 1; i < curNums.length; ++i) {
            let cur = curNums[i];
            let prev = curNums[i - 1];
            let n = cur - prev;
            res.push(n);
        }
        return res;
    }

    while (true) {
        /** @type Set<number>*/
        let set = new Set();
        let curDifs = getCurDifs(curNums);
        for (let d of curDifs) {
            set.add(d);
        }

        res.push(curDifs);
        curNums = curDifs;
        if (set.size === 1) {
            break;
        }
    }
    res.reverse();
    return res;
}
