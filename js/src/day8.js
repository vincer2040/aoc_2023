// @ts-check

/**
 * @param {string} input
 * @returns {number}
 */
export function p1(input) {
    let split = input.split("\n\n");
    let instructions = split[0].split("");
    let map = split[1].split("\n").filter(x => x.length);
    /** @type Map<string, [string, string]>*/
    const dict = new Map();
    for (let row of map) {
        let [from, leftRight] = row.split(" = ");
        let [left, right] = leftRight.split(", ");
        left = left.replace("(", "");
        right = right.replace(")", "");
        dict.set(from, [left, right]);
    }
    return walk(dict, "AAA", instructions, 0, 0);
}

/**
 * @param {string} input
 * @returns {number}
 */
export function p2(input) {
    let split = input.split("\n\n");
    let instructions = split[0].split("");
    let map = split[1].split("\n").filter(x => x.length);
    /** @type Map<string, [string, string]>*/
    const dict = new Map();
    for (let row of map) {
        let [from, leftRight] = row.split(" = ");
        let [left, right] = leftRight.split(", ");
        left = left.replace("(", "");
        right = right.replace(")", "");
        dict.set(from, [left, right]);
    }

    /** @type number[] */
    let steps = [];
    for (let key of dict.keys()) {
        if (!key.endsWith('A')) {
            continue;
        }
        let numSteps = walk2(dict, key, instructions, 0, 0);
        steps.push(numSteps);
    }
    return lcmOfArr(steps);
}

/**
 * @param {Map<string, [string, string]>} dict
 * @param {string} curLocation
 * @param {string[]} instructions
 * @param {number} instructionsIdx
 * @param {number} numSteps
 * @returns {number}
 */
function walk(dict, curLocation, instructions, instructionsIdx, numSteps) {
    while (curLocation !== "ZZZ") {
        let instruction = instructions[instructionsIdx % instructions.length];
        let leftRight = dict.get(curLocation);
        if (instruction === 'L') {
            // @ts-ignore:
            curLocation = leftRight[0];
        }
        if (instruction === 'R') {
            // @ts-ignore:
            curLocation = leftRight[1];
        }
        instructionsIdx++;
        numSteps++;
    }
    return numSteps;
}

/**
 * @param {Map<string, [string, string]>} dict
 * @param {string} curLocation
 * @param {string[]} instructions
 * @param {number} instructionsIdx
 * @param {number} numSteps
 * @returns {number}
 */
function walk2(dict, curLocation, instructions, instructionsIdx, numSteps) {
    while (!curLocation.endsWith('Z')) {
        let instruction = instructions[instructionsIdx % instructions.length];
        let leftRight = dict.get(curLocation);
        if (instruction === 'L') {
            // @ts-ignore:
            curLocation = leftRight[0];
        }
        if (instruction === 'R') {
            // @ts-ignore:
            curLocation = leftRight[1];
        }
        instructionsIdx++;
        numSteps++;
    }
    return numSteps;
}

/**
 * @param {number} a
 * @param {number} b
 * @returns {number}
 */
function gcd(a, b) {
    if (b === 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

/**
 * @param {number} a
 * @param {number} b
 * @returns {number}
 */
function lcm(a, b) {
    return (a * b) / gcd(a, b);
}

/**
 * @param {number[]} arr
 * @returns {number}
 */
function lcmOfArr(arr) {
    let result = arr[0];
    for (let i = 1; i < arr.length; ++i) {
        result = lcm(result, arr[i]);
    }
    return result;
}
