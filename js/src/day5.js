// @ts-check
/// <reference path = "./day5.d.ts" />

/**
 * @param {string} input
 * @returns {number} result
 */
export function p1(input) {
    let data = input.split("\n\n").filter(l => l.length);
    let seeds = data.shift()?.replace("seeds: ", "").split(" ");
    let endNums = [];
    if (seeds) {
        for (let seed of seeds) {
            let s = parseInt(seed);
            for (let d of data) {
                let map = d.split("\n").filter(s => s.length);
                map.shift();
                for (let chunk of map) {
                    let numbers = chunk.split(" ").map(n => parseInt(n));
                    let dst = numbers[0];
                    let src = numbers[1];
                    let range = numbers[2];
                    if (s >= src && s <= src + range) {
                        s += dst - src;
                        break;
                    }
                }
            }
            endNums.push(s);
        }
    } else {
        return 0;
    }

    let res = endNums.reduce((a, b) => Math.min(a, b), endNums[0]);
    return res;
}

/**
 * @param {string} input
 * @returns {number} result
 */
export function p2(input) {
    let contents = input.split("\n\n").filter(l => l.length);
    let seedValues = contents.shift()?.replace("seeds: ", "").split(" ");
    const seeds = [];
    // @ts-ignore:
    for (let i = 0; i < seedValues?.length; i += 2) {
        seeds.push({
            // @ts-ignore:
            start: parseInt(seedValues[i]),
            // @ts-ignore:
            length: parseInt(seedValues[i + 1]),
        });
    }
    /** @type MapItem[] */
    let data = contents.map((m) => {
        let split = m.split("\n");
        let fromToString = split.shift()?.split(" ")[0];
        // @ts-ignore
        let [from, _, to] = fromToString.split("-");
        /** @type RangeT[] */
        let map = split.map((row) => {
            let [dst, src, range] = row.split(" ").map(num => parseInt(num))
            return { dst, src, range };
        });
        let obj = { from, to, map };
        return obj
    });
    /**
     * @param {RangeT[]} ranges
     */
    function createNegativeRanges(ranges) {
        ranges.sort((a, b) => a.src - b.src);
        let start = 0;
        for (let i = 0; i < ranges.length; ++i) {
            const range = ranges[i];
            if (range.src > start) {
                ranges.splice(i, 0, {
                    src: start,
                    dst: start,
                    range: range.src - start,
                })
                i++;
            }
            start = range.src + range.range;
        }
        return ranges;
    }

    data.forEach((p) => {
        createNegativeRanges(p.map);
    });

    const map = data.reduce((acc, x) => {
        acc[x.from] = x;
        return acc;
    }, {});

    let lowest = Infinity;

    for (const seed of seeds) {
        let remaining = seed.length;
        let start = seed.start;
        while (remaining > 0) {
            const [startLocation, consumed] = walk(start, remaining, "seed", map);
            remaining -= consumed;
            start += consumed;
            if (startLocation < lowest) {
                lowest = startLocation;
            }
        }
    }
    return lowest;
}

/**
 * @param {number} value
 * @param {number} range
 * @param {string} name
 * @param {DataMap} map
 * @returns {[number, number]}
 */
function walk(value, range, name, map) {
    if (map[name] === undefined) {
        return [value, range];
    }
    const item = map[name];
    const rangeItem = item.map.find(x => x.src <= value && value < x.src + x.range);
    if (rangeItem) {
        const dif = value - rangeItem.src;
        const newValue = rangeItem.dst + dif;
        return walk(newValue, Math.min(range, rangeItem.range - dif), item.to, map);
    }
    return walk(value, 1, item.to, map);
}
