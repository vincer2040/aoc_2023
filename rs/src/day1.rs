pub fn part_one(input: &str) -> i32 {
    let t = input.lines().into_iter().fold(0, |acc, l| {
        let first = l.chars().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let last = l.chars().rev().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let t = format!("{}{}", first, last);
        let res: i32 = t.parse().unwrap();
        acc + res
    });
    return t;
}

pub fn part_two(input: &str) -> i32 {
    let t = input.lines().fold(0, |acc, l| {
        let mut s = l.replace("one", "one1one");
        s = s.replace("two", "two2two");
        s = s.replace("three", "three3three");
        s = s.replace("four", "four4four");
        s = s.replace("five", "five5five");
        s = s.replace("six", "six6six");
        s = s.replace("seven", "seven7seven");
        s = s.replace("eight", "eight8eight");
        s = s.replace("nine", "nine9nine");
        let first = s.chars().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let last = s.chars().rev().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let t = format!("{}{}", first, last);
        let res: i32 = t.parse().unwrap();
        acc + res
    });
    return t;
}

#[cfg(test)]
mod test {
    use super::{part_one, part_two};

    #[test]
    fn part_one_test() {
        let input = r#"1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet"#;
        let res = part_one(input);
        assert_eq!(res, 142);
    }

    #[test]
    fn parse_two_test() {
        let input = r#"two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen"#;
        let res = part_two(input);
        assert_eq!(res, 281);
    }
}

