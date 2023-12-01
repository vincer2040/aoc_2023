pub fn part_one(input: &str) {
    let t = input.lines().into_iter().fold(0, |acc, l| {
        let first = l.chars().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let last = l.chars().rev().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let t = format!("{}{}", first, last);
        let res: i32 = t.parse().unwrap();
        acc + res
    });
    println!("{}", t);
}

pub fn part_two(input: &str) {
    let t = input.lines().fold(0, |acc, l| {
        println!("{}", l);
        let mut s = l.replace("one", "one1one");
        s = s.replace("two", "two2two");
        s = s.replace("three", "three3three");
        s = s.replace("four", "four4four");
        s = s.replace("five", "five5five");
        s = s.replace("six", "six6six");
        s = s.replace("seven", "seven7seven");
        s = s.replace("eight", "eight8eight");
        s = s.replace("nine", "nine9nine");
        println!("{}", s);
        let first = s.chars().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let last = s.chars().rev().find(|ch| '0' <= *ch && *ch <= '9').unwrap();
        let t = format!("{}{}", first, last);
        let res: i32 = t.parse().unwrap();
        acc + res
    });
    println!("{}", t);
}
