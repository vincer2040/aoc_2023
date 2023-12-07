// @ts-check
/// <reference path = "./day7.d.ts" />

/** @type Record<string, HandResultType> */
const HandResult = {
    HighCard: 0,
    OnePair: 1,
    TwoPair: 2,
    ThreeOfAKind: 3,
    FullHouse: 4,
    FourOfAKind: 5,
    FiveOfAKind: 6,
};

/**
 * @param {string} input
 * @returns {number}
 */
export function p1(input) {
    /** @type HandData[] */
    let hands_bids = input.split("\n").filter(l => l.length).map(l => {
        let [hand, bid] = l.split(' ');
        let calculated = calculateHand(hand);
        /** @type HandData */
        let result = [calculated, hand, parseInt(bid)];
        return result;
    });

    hands_bids.sort(([acalculated, ahand, _a], [bcalculated, bhand, _b]) => {
        if (acalculated !== bcalculated) {
            return acalculated - bcalculated;
        } else {
            let orderedA = orderString(ahand);
            let orderedB = orderString(bhand);
            return orderedA.localeCompare(orderedB);
        }
    });

    let result = hands_bids.reduce((acc, [_a, _b, bid], i) => {
        return acc + ((i + 1) * bid);
    }, 0);

    return result;
}

/**
 * @param {string} input
 * @returns {number}
 */
export function p2(input) {
    /** @type HandData[] */
    let hands_bids = input.split("\n").filter(l => l.length).map(l => {
        let [hand, bid] = l.split(' ');
        let calculated = calculateHand2(hand);
        /** @type HandData */
        let result = [calculated, hand, parseInt(bid)];
        return result;
    });

    hands_bids.sort(([acalculated, ahand, _a], [bcalculated, bhand, _b]) => {
        if (acalculated !== bcalculated) {
            return acalculated - bcalculated;
        } else {
            let orderedA = orderString2(ahand);
            let orderedB = orderString2(bhand);
            return orderedA.localeCompare(orderedB);
        }
    });

    let result = hands_bids.reduce((acc, [_a, _b, bid], i) => {
        return acc + ((i + 1) * bid);
    }, 0);

    return result;
}

/**
 * @param {string} hand
 * @returns {HandResultType}
 */
function calculateHand(hand) {
    /** @type Map<string, number> */
    let map = new Map();

    for (let ch of hand) {
        if (map.has(ch)) {
            let old = map.get(ch);
            // seriously? why does typescript have to be told to ignore this? we literally
            // just checked to see if it was there there's no change its undefined...
            // @ts-ignore:
            map.set(ch, old + 1);
        } else {
            map.set(ch, 1);
        }
    }

    let result = Object.values(Array.from(map)).reduce((acc, [_, value]) => {
        switch (value) {
            case 1:
                break;
            case 2:
                if (acc === HandResult.HighCard) {
                    acc = HandResult.OnePair;
                } else if (acc === HandResult.OnePair) {
                    acc = HandResult.TwoPair;
                } else if (acc === HandResult.ThreeOfAKind) {
                    acc = HandResult.FullHouse;
                }
                break;
            case 3:
                if (acc === HandResult.HighCard) {
                    acc = HandResult.ThreeOfAKind;
                } else if (acc == HandResult.OnePair) {
                    acc = HandResult.FullHouse;
                }
                break;
            case 4:
                acc = HandResult.FourOfAKind;
                break;
            case 5:
                acc = HandResult.FiveOfAKind;
                break;
        }
        return acc;
    }, HandResult.HighCard);

    return result;
}

/**
 * @param {string} hand
 * @returns {HandResultType}
 */
function calculateHand2(hand) {
    /** @type Map<string, number> */
    let map = new Map();

    for (let ch of hand) {
        if (map.has(ch)) {
            let old = map.get(ch);
            // seriously? why does typescript have to be told to ignore this? we literally
            // just checked to see if it was there there's no change its undefined...
            // @ts-ignore:
            map.set(ch, old + 1);
        } else {
            map.set(ch, 1);
        }
    }

    let result = Object.values(Array.from(map)).reduce((acc, [_, value]) => {
        switch (value) {
            case 1:
                break;
            case 2:
                if (acc === HandResult.HighCard) {
                    acc = HandResult.OnePair;
                } else if (acc === HandResult.OnePair) {
                    acc = HandResult.TwoPair;
                } else if (acc === HandResult.ThreeOfAKind) {
                    acc = HandResult.FullHouse;
                }
                break;
            case 3:
                if (acc === HandResult.HighCard) {
                    acc = HandResult.ThreeOfAKind;
                } else if (acc == HandResult.OnePair) {
                    acc = HandResult.FullHouse;
                }
                break;
            case 4:
                acc = HandResult.FourOfAKind;
                break;
            case 5:
                acc = HandResult.FiveOfAKind;
                break;
        }
        return acc;
    }, HandResult.HighCard);

    let newResult = result;

    switch (result) {
        case HandResult.HighCard:
            if (map.has('J')) {
                newResult = HandResult.OnePair;
            }
            break;
        case HandResult.OnePair:
            if (map.has('J')) {
                newResult = HandResult.ThreeOfAKind;
            }
            break;
        case HandResult.TwoPair:
            if (map.has('J')) {
                let amtJ = map.get('J');
                if (amtJ === 1) {
                    newResult = HandResult.FullHouse;
                } else if (amtJ === 2) {
                    newResult = HandResult.FourOfAKind;
                }
            }
            break;
        case HandResult.ThreeOfAKind:
            if (map.has('J')) {
                newResult = HandResult.FourOfAKind;
            }
            break;
        case HandResult.FullHouse:
            if (map.has('J')) {
                newResult = HandResult.FiveOfAKind;
            }
            break;
        case HandResult.FourOfAKind:
            if (map.has('J')) {
                newResult = HandResult.FiveOfAKind;
            }
            break;
    }

    return newResult;
}

/**
 * @param {string} hand
 * @return {string}
 */
function orderString(hand) {
    return hand.split("").reduce((acc, cur) => {
        let nextChar;
        switch (cur) {
            case '2':
                nextChar = "a";
                break;
            case '3':
                nextChar = "b";
                break;
            case '4':
                nextChar = "c";
                break;
            case '5':
                nextChar = "d";
                break;
            case '6':
                nextChar = "e";
                break;
            case '7':
                nextChar = "f";
                break;
            case '8':
                nextChar = "g";
                break;
            case '9':
                nextChar = "h";
                break;
            case 'T':
                nextChar = "i";
                break;
            case 'J':
                nextChar = "j";
                break;
            case 'Q':
                nextChar = "k";
                break;
            case 'K':
                nextChar = "l";
                break;
            case 'A':
                nextChar = "m";
                break;
        }
        return acc + nextChar;
    }, "");
}


/**
 * @param {string} hand
 * @return {string}
 */
function orderString2(hand) {
    return hand.split("").reduce((acc, cur) => {
        let nextChar;
        switch (cur) {
            case 'A':
                nextChar = 'z';
                break;
            case 'K':
                nextChar = 'y';
                break;
            case 'Q':
                nextChar = 'x';
                break;
            case 'T':
                nextChar = 'w';
                break;
            case '9':
                nextChar = 'v';
                break;
            case '8':
                nextChar = 'u';
                break;
            case '7':
                nextChar = 't';
                break;
            case '6':
                nextChar = 's';
                break;
            case '5':
                nextChar = 'r';
                break;
            case '4':
                nextChar = 'q';
                break;
            case '3':
                nextChar = 'p';
                break;
            case '2':
                nextChar = 'o';
                break;
            case '1':
                nextChar = 'n';
                break;
            case 'J':
                nextChar = 'm';
                break;
        }
        return acc + nextChar;
    }, "");
}

