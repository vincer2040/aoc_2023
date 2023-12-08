package aoc;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Scanner;

public class DaySeven {

    private String input;

    enum HandResult {
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfAKind,
        FullHouse,
        FourOfAKind,
        FiveOfAKind,
    }

    class Hand {
        public HandResult result;
        public String hand;
        public int bid;

        public Hand(HandResult result, String hand, int bid) {
            this.result = result;
            this.hand = hand;
            this.bid = bid;
        }

        public String orderedString() {
            String res = new String();
            for (int ch : this.hand.chars().toArray()) {
                char c = (char) ch;
                switch (c) {
                    case 'A':
                        res += 'z';
                        break;
                    case 'K':
                        res += 'y';
                        break;
                    case 'Q':
                        res += 'x';
                        break;
                    case 'J':
                        res += 'w';
                        break;
                    case 'T':
                        res += 'v';
                        break;
                    case '9':
                        res += 'u';
                        break;
                    case '8':
                        res += 't';
                        break;
                    case '7':
                        res += 's';
                        break;
                    case '6':
                        res += 'r';
                        break;
                    case '5':
                        res += 'q';
                        break;
                    case '4':
                        res += 'p';
                        break;
                    case '3':
                        res += 'o';
                        break;
                    case '2':
                        res += 'n';
                        break;
                    case '1':
                        res += 'm';
                        break;
                }
            }
            return res;
        }

        public String orderedString2() {
            String res = new String();
            for (int ch : this.hand.chars().toArray()) {
                char c = (char) ch;
                switch (c) {
                    case 'A':
                        res += 'z';
                        break;
                    case 'K':
                        res += 'y';
                        break;
                    case 'Q':
                        res += 'x';
                        break;
                    case 'T':
                        res += 'w';
                        break;
                    case '9':
                        res += 'v';
                        break;
                    case '8':
                        res += 'u';
                        break;
                    case '7':
                        res += 't';
                        break;
                    case '6':
                        res += 's';
                        break;
                    case '5':
                        res += 'r';
                        break;
                    case '4':
                        res += 'q';
                        break;
                    case '3':
                        res += 'p';
                        break;
                    case '2':
                        res += 'o';
                        break;
                    case '1':
                        res += 'n';
                        break;
                    case 'J':
                        res += 'm';
                        break;
                }
            }
            return res;
        }
    }

    class HandComparitor implements Comparator<Hand> {
        @Override
        public int compare(Hand a, Hand b) {
            if (a.result != b.result) {
                return a.result.ordinal() - b.result.ordinal();
            }
            String orderedA = a.orderedString();
            String orderedB = b.orderedString();
            return orderedA.compareTo(orderedB);
        }
    }

    class HandComparitor2 implements Comparator<Hand> {
        @Override
        public int compare(Hand a, Hand b) {
            if (a.result != b.result) {
                return a.result.ordinal() - b.result.ordinal();
            }
            String orderedA = a.orderedString2();
            String orderedB = b.orderedString2();
            return orderedA.compareTo(orderedB);
        }
    }

    public DaySeven(String input) {
        this.input = input;
    }

    public int p1() {
        int res = 0;
        Scanner scanner = new Scanner(this.input);
        ArrayList<Hand> hands = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] hand_bid = line.split(" ");
            String hand = hand_bid[0];
            int bid = Integer.parseInt(hand_bid[1]);
            HandResult result = calculateHand(hand);
            Hand h = new Hand(result, hand, bid);
            hands.add(h);
        }
        scanner.close();

        Collections.sort(hands, new HandComparitor());
        int i, len = hands.size();

        for (i = 0; i < len; ++i) {
            Hand hand = hands.get(i);
            res += (i * hand.bid);
        }
        return res;
    }

    public int p2() {
        int res = 0;
        Scanner scanner = new Scanner(this.input);
        ArrayList<Hand> hands = new ArrayList<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] hand_bid = line.split(" ");
            String hand = hand_bid[0];
            int bid = Integer.parseInt(hand_bid[1]);
            HandResult result = calculateHand2(hand);
            Hand h = new Hand(result, hand, bid);
            hands.add(h);
        }
        scanner.close();

        Collections.sort(hands, new HandComparitor2());
        int i, len = hands.size();

        for (i = 0; i < len; ++i) {
            Hand hand = hands.get(i);
            res += (i * hand.bid);
        }
        return res;
    }

    private HandResult calculateHand(String hand) {
        HandResult res = HandResult.HighCard;
        HashMap<Character, Integer> map = new HashMap<>();
        for (int ch : hand.chars().toArray()) {
            char c = (char) ch;
            if (map.containsKey(c)) {
                int old = map.get(c);
                int new_v = old + 1;
                map.replace(c, new_v);
            } else {
                map.put(c, 1);
            }
        }

        for (HashMap.Entry<Character, Integer> e : map.entrySet()) {
            int value = e.getValue();
            switch (value) {
                case 1:
                    break;
                case 2:
                    switch (res) {
                        case HighCard:
                            res = HandResult.OnePair;
                            break;
                        case OnePair:
                            res = HandResult.TwoPair;
                            break;
                        case ThreeOfAKind:
                            res = HandResult.FullHouse;
                            break;
                        default:
                            break;
                    }
                    break;
                case 3:
                    switch (res) {
                        case HighCard:
                            res = HandResult.ThreeOfAKind;
                            break;
                        case OnePair:
                            res = HandResult.FullHouse;
                            break;
                        default:
                            break;
                    }
                    break;
                case 4:
                    res = HandResult.FourOfAKind;
                    break;
                case 5:
                    res = HandResult.FiveOfAKind;
                default:
                    break;
            }
        }
        return res;
    }

    private HandResult calculateHand2(String hand) {
        HandResult res = HandResult.HighCard;
        HashMap<Character, Integer> map = new HashMap<>();
        for (int ch : hand.chars().toArray()) {
            char c = (char) ch;
            if (map.containsKey(c)) {
                int old = map.get(c);
                int new_v = old + 1;
                map.replace(c, new_v);
            } else {
                map.put(c, 1);
            }
        }

        for (HashMap.Entry<Character, Integer> e : map.entrySet()) {
            int value = e.getValue();
            switch (value) {
                case 1:
                    break;
                case 2:
                    switch (res) {
                        case HighCard:
                            res = HandResult.OnePair;
                            break;
                        case OnePair:
                            res = HandResult.TwoPair;
                            break;
                        case ThreeOfAKind:
                            res = HandResult.FullHouse;
                            break;
                        default:
                            break;
                    }
                    break;
                case 3:
                    switch (res) {
                        case HighCard:
                            res = HandResult.ThreeOfAKind;
                            break;
                        case OnePair:
                            res = HandResult.FullHouse;
                            break;
                        default:
                            break;
                    }
                    break;
                case 4:
                    res = HandResult.FourOfAKind;
                    break;
                case 5:
                    res = HandResult.FiveOfAKind;
                default:
                    break;
            }
        }

        boolean hasJ = map.containsKey('J');
        int numJ = 0;
        if (hasJ) {
            numJ = map.get('J');
        }
        HandResult newResult = res;
        switch (res) {
            case HighCard:
                if (hasJ) {
                    newResult = HandResult.OnePair;
                }
                break;
            case OnePair:
                if (hasJ) {
                    newResult = HandResult.ThreeOfAKind;
                }
                break;
            case TwoPair:
                if (hasJ) {
                    if (numJ == 1) {
                        newResult = HandResult.FullHouse;
                    } else if (numJ == 2) {
                        newResult = HandResult.FourOfAKind;
                    }
                }
                break;
            case ThreeOfAKind:
                if (hasJ) {
                    newResult = HandResult.FourOfAKind;
                }
                break;
            case FullHouse:
                if (hasJ) {
                    newResult = HandResult.FiveOfAKind;
                }
                break;
            case FourOfAKind:
                if (hasJ) {
                    newResult = HandResult.FiveOfAKind;
                }
                break;
            default:
                break;
        }

        return newResult;
    }
}
