#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
enum HandResult {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind,
}

pub fn part_one(input: &str) -> usize {
    let mut hands_bids: Vec<(HandResult, &str, usize)> = input
        .lines()
        .map(|l| {
            let mut split = l.split(' ');
            let hand = split.nth(0).unwrap();
            let bid: usize = split.nth(0).unwrap().parse().unwrap();
            let calculated = calculate_hand(hand);
            return (calculated, hand, bid);
        })
        .collect();

    hands_bids.sort_by(|(ahand_res, ahand, _), (bhand_res, bhand, _)| {
        if ahand_res != bhand_res {
            ahand_res.cmp(bhand_res)
        } else {
            let ordered_a = ordered_string(ahand);
            let ordered_b = ordered_string(bhand);
            ordered_a.cmp(&ordered_b)
        }
    });

    let result = hands_bids
        .iter()
        .enumerate()
        .fold(0, |acc, (i, (_, _, bid))| acc + ((i + 1) * bid));
    result
}

pub fn part_two(input: &str) -> usize {
    let mut hands_bids: Vec<(HandResult, &str, usize)> = input
        .lines()
        .map(|l| {
            let mut split = l.split(' ');
            let hand = split.nth(0).unwrap();
            let bid: usize = split.nth(0).unwrap().parse().unwrap();
            let calculated = calculate_hand2(hand);
            return (calculated, hand, bid);
        })
        .collect();

    hands_bids.sort_by(|(ahand_res, ahand, _), (bhand_res, bhand, _)| {
        if ahand_res != bhand_res {
            ahand_res.cmp(bhand_res)
        } else {
            let ordered_a = ordered_string2(ahand);
            let ordered_b = ordered_string2(bhand);
            ordered_a.cmp(&ordered_b)
        }
    });

    let result = hands_bids
        .iter()
        .enumerate()
        .fold(0, |acc, (i, (_, _, bid))| acc + ((i + 1) * bid));
    result
}

fn ordered_string(hand: &str) -> String {
    hand.chars().fold(String::new(), |mut acc, ch| {
        let cur = match ch {
            '2' => 'a',
            '3' => 'b',
            '4' => 'c',
            '5' => 'd',
            '6' => 'e',
            '7' => 'f',
            '8' => 'g',
            '9' => 'h',
            'T' => 'i',
            'J' => 'j',
            'Q' => 'k',
            'K' => 'l',
            'A' => 'm',
            _ => unreachable!(),
        };
        acc.push(cur);
        acc
    })
}

fn ordered_string2(hand: &str) -> String {
    hand.chars().fold(String::new(), |mut acc, ch| {
        let cur = match ch {
            'A' => 'z',
            'K' => 'y',
            'Q' => 'x',
            'T' => 'w',
            '9' => 'v',
            '8' => 'u',
            '7' => 't',
            '6' => 's',
            '5' => 'r',
            '4' => 'q',
            '3' => 'p',
            '2' => 'o',
            '1' => 'n',
            'J' => 'm',
            _ => unreachable!(),
        };
        acc.push(cur);
        acc
    })
}

fn calculate_hand(hand: &str) -> HandResult {
    let mut map: std::collections::HashMap<char, u32> = std::collections::HashMap::new();
    for ch in hand.chars() {
        if map.contains_key(&ch) {
            let old = map.get(&ch).unwrap();
            let new = old + 1;
            map.insert(ch, new);
        } else {
            map.insert(ch, 1);
        }
    }
    map.iter()
        .fold(HandResult::HighCard, |acc, (_, value)| match value {
            1 => acc,
            2 => match acc {
                HandResult::HighCard => HandResult::OnePair,
                HandResult::OnePair => HandResult::TwoPair,
                HandResult::ThreeOfAKind => HandResult::FullHouse,
                _ => unreachable!(),
            },
            3 => match acc {
                HandResult::HighCard => HandResult::ThreeOfAKind,
                HandResult::OnePair => HandResult::FullHouse,
                _ => unreachable!(),
            },
            4 => HandResult::FourOfAKind,
            5 => HandResult::FiveOfAKind,
            _ => unreachable!(),
        })
}

fn calculate_hand2(hand: &str) -> HandResult {
    let mut map: std::collections::HashMap<char, u32> = std::collections::HashMap::new();
    for ch in hand.chars() {
        if map.contains_key(&ch) {
            let old = map.get(&ch).unwrap();
            let new = old + 1;
            map.insert(ch, new);
        } else {
            map.insert(ch, 1);
        }
    }
    let result = map
        .iter()
        .fold(HandResult::HighCard, |acc, (_, value)| match value {
            1 => acc,
            2 => match acc {
                HandResult::HighCard => HandResult::OnePair,
                HandResult::OnePair => HandResult::TwoPair,
                HandResult::ThreeOfAKind => HandResult::FullHouse,
                _ => unreachable!(),
            },
            3 => match acc {
                HandResult::HighCard => HandResult::ThreeOfAKind,
                HandResult::OnePair => HandResult::FullHouse,
                _ => unreachable!(),
            },
            4 => HandResult::FourOfAKind,
            5 => HandResult::FiveOfAKind,
            _ => unreachable!(),
        });

    let new_result = match result {
        HandResult::HighCard => {
            if map.contains_key(&'J') {
                HandResult::OnePair
            } else {
                HandResult::HighCard
            }
        }
        HandResult::OnePair => {
            if map.contains_key(&'J') {
                HandResult::ThreeOfAKind
            } else {
                HandResult::OnePair
            }
        }
        HandResult::TwoPair => {
            if map.contains_key(&'J') {
                match map.get(&'J').unwrap() {
                    1 => HandResult::FullHouse,
                    2 => HandResult::FourOfAKind,
                    _ => unreachable!(),
                }
            } else {
                HandResult::TwoPair
            }
        }
        HandResult::ThreeOfAKind => {
            if map.contains_key(&'J') {
                HandResult::FourOfAKind
            } else {
                HandResult::ThreeOfAKind
            }
        }
        HandResult::FullHouse => {
            if map.contains_key(&'J') {
                HandResult::FiveOfAKind
            } else {
                HandResult::FullHouse
            }
        }
        HandResult::FourOfAKind => {
            if map.contains_key(&'J') {
                HandResult::FiveOfAKind
            } else {
                HandResult::FourOfAKind
            }
        }
        HandResult::FiveOfAKind => HandResult::FiveOfAKind,
    };
    new_result
}
