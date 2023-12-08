#include "aoc.hh"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum class hand_result {
    HighCard = 0,
    OnePair = 1,
    TwoPair = 2,
    ThreeOfAKind = 3,
    FullHouse = 4,
    FourOfAKind = 5,
    FiveOfAKind = 6,
};

struct hand_data {
    hand_result result;
    std::string hand;
    int bid;
};

static hand_result calculate_hand(const std::string& hand);
static hand_result calculate_hand2(const std::string& hand);
static std::string order_string(const std::string& hand);
static std::string order_string2(const std::string& hand);
static bool compare(hand_data a, hand_data b);
static bool compare2(hand_data a, hand_data b);

int day7p1(const std::string& input) {
    int res = 0;
    std::vector<std::string> split = split_str(input, '\n');
    std::vector<hand_data> hands;
    for (auto& hand_str : split) {
        std::vector<std::string> hand_bid = split_str(hand_str, ' ');
        std::string hand = hand_bid[0];
        int bid = stoi(hand_bid[1]);
        hand_result res = calculate_hand(hand);
        hand_data hd = {res, hand, bid};
        hands.push_back(hd);
    }

    std::sort(hands.begin(), hands.end(), compare);

    size_t i, len = hands.size();
    for (i = 0; i < len; ++i) {
        res += ((i + 1) * hands[i].bid);
    }

    return res;
}

int day7p2(const std::string& input) {
    int res = 0;
    std::vector<std::string> split = split_str(input, '\n');
    std::vector<hand_data> hands;
    for (auto& hand_str : split) {
        std::vector<std::string> hand_bid = split_str(hand_str, ' ');
        std::string hand = hand_bid[0];
        int bid = stoi(hand_bid[1]);
        hand_result res = calculate_hand2(hand);
        hand_data hd = {res, hand, bid};
        hands.push_back(hd);
    }

    std::sort(hands.begin(), hands.end(), compare2);

    size_t i, len = hands.size();
    for (i = 0; i < len; ++i) {
        res += ((i + 1) * hands[i].bid);
    }

    return res;
}

static hand_result calculate_hand(const std::string& hand) {
    hand_result res = hand_result::HighCard;
    std::unordered_map<char, int> map;

    for (auto ch : hand) {
        if (map.find(ch) != map.end()) {
            int old = map[ch];
            map[ch] = old + 1;
        } else {
            map[ch] = 1;
        }
    }

    for (auto& kv : map) {
        int value = kv.second;
        switch (value) {
        case 1:
            break;
        case 2:
            switch (res) {
            case hand_result::HighCard:
                res = hand_result::OnePair;
                break;
            case hand_result::OnePair:
                res = hand_result::TwoPair;
                break;
            case hand_result::ThreeOfAKind:
                res = hand_result::FullHouse;
                break;
            default:
                break;
            }
            break;
        case 3:
            switch (res) {
            case hand_result::HighCard:
                res = hand_result::ThreeOfAKind;
                break;
            case hand_result::OnePair:
                res = hand_result::FullHouse;
                break;
            default:
                break;
            }
            break;
        case 4:
            res = hand_result::FourOfAKind;
            break;
        case 5:
            res = hand_result::FiveOfAKind;
            break;
        }
    }

    return res;
}

static hand_result calculate_hand2(const std::string& hand) {
    hand_result res = hand_result::HighCard;
    std::unordered_map<char, int> map;

    for (auto ch : hand) {
        if (map.find(ch) != map.end()) {
            int old = map[ch];
            map[ch] = old + 1;
        } else {
            map[ch] = 1;
        }
    }

    for (auto& kv : map) {
        int value = kv.second;
        switch (value) {
        case 1:
            break;
        case 2:
            switch (res) {
            case hand_result::HighCard:
                res = hand_result::OnePair;
                break;
            case hand_result::OnePair:
                res = hand_result::TwoPair;
                break;
            case hand_result::ThreeOfAKind:
                res = hand_result::FullHouse;
                break;
            default:
                break;
            }
            break;
        case 3:
            switch (res) {
            case hand_result::HighCard:
                res = hand_result::ThreeOfAKind;
                break;
            case hand_result::OnePair:
                res = hand_result::FullHouse;
                break;
            default:
                break;
            }
            break;
        case 4:
            res = hand_result::FourOfAKind;
            break;
        case 5:
            res = hand_result::FiveOfAKind;
            break;
        }
    }

    hand_result new_result = res;

    bool has_j = map.find('j') != map.end();
    int num_j = map['j'];

    switch (res) {
    case hand_result::HighCard:
        if (has_j) {
            new_result = hand_result::OnePair;
        }
        break;
    case hand_result::OnePair:
        if (has_j) {
            new_result = hand_result::ThreeOfAKind;
        }
        break;
    case hand_result::TwoPair:
        if (has_j) {
            if (num_j == 1) {
                new_result = hand_result::FullHouse;
            } else if (num_j == 2) {
                new_result = hand_result::FourOfAKind;
            }
        }
        break;
    case hand_result::ThreeOfAKind:
        if (has_j) {
            new_result = hand_result::FourOfAKind;
        }
        break;
    case hand_result::FullHouse:
        if (has_j) {
            new_result = hand_result::FiveOfAKind;
        }
        break;
    case hand_result::FourOfAKind:
        if (has_j) {
            new_result = hand_result::FiveOfAKind;
        }
        break;
    default:
        break;
    }

    return new_result;
}

static std::string order_string(const std::string& hand) {
    std::string res;
    for (auto ch : hand) {
        switch (ch) {
        case 'A':
            res.push_back('z');
            break;
        case 'K':
            res.push_back('y');
            break;
        case 'Q':
            res.push_back('x');
            break;
        case 'J':
            res.push_back('w');
            break;
        case 'T':
            res.push_back('v');
            break;
        case '9':
            res.push_back('u');
            break;
        case '8':
            res.push_back('t');
            break;
        case '7':
            res.push_back('s');
            break;
        case '6':
            res.push_back('r');
            break;
        case '5':
            res.push_back('q');
            break;
        case '4':
            res.push_back('p');
            break;
        case '3':
            res.push_back('o');
            break;
        case '2':
            res.push_back('n');
            break;
        case '1':
            res.push_back('m');
            break;
        }
    }
    return res;
}

static std::string order_string2(const std::string& hand) {
    std::string res;
    for (auto ch : hand) {
        switch (ch) {
        case 'A':
            res.push_back('z');
            break;
        case 'K':
            res.push_back('y');
            break;
        case 'Q':
            res.push_back('x');
            break;
        case 'T':
            res.push_back('w');
            break;
        case '9':
            res.push_back('v');
            break;
        case '8':
            res.push_back('u');
            break;
        case '7':
            res.push_back('t');
            break;
        case '6':
            res.push_back('s');
            break;
        case '5':
            res.push_back('r');
            break;
        case '4':
            res.push_back('q');
            break;
        case '3':
            res.push_back('p');
            break;
        case '2':
            res.push_back('o');
            break;
        case '1':
            res.push_back('n');
            break;
        case 'J':
            res.push_back('m');
            break;
        }
    }
    return res;
}

static bool compare(hand_data a, hand_data b) {
    if (a.result != b.result) {
        return a.result < b.result;
    }

    std::string as = order_string(a.hand);
    std::string bs = order_string(b.hand);
    return as < bs;
}

static bool compare2(hand_data a, hand_data b) {
    if (a.result != b.result) {
        return a.result < b.result;
    }

    std::string as = order_string2(a.hand);
    std::string bs = order_string2(b.hand);
    return as < bs;
}
