#[derive(Debug)]
enum Color {
    Blue(i32),
    Red(i32),
    Green(i32),
}

impl Color {
    pub fn new(num: i32, input: &str) -> Color {
        match input {
            "blue" => Color::Blue(num),
            "red" => Color::Red(num),
            "green" => Color::Green(num),
            _ => unreachable!(),
        }
    }
}

fn is_possible(color: &Color) -> bool {
    match color {
        Color::Blue(val) => *val <= 14,
        Color::Red(val) => *val <= 12,
        Color::Green(val) => *val <= 13,
    }
}

pub fn part_one(input: &str) -> i32 {
    let res = input.lines().fold(0, |mut acc, l| {
        let split = l.split(": ").into_iter().collect::<Vec<&str>>();
        let game: i32 = split[0].replace("Game ", "").parse().unwrap();
        let contents = split[1];
        let set_strs = contents.split("; ").collect::<Vec<&str>>();
        let set = set_strs.iter().fold(vec![], |mut acc, s| {
            let set_colors_inp = s.split(", ").collect::<Vec<&str>>();
            let set_colors: Vec<Color> = set_colors_inp
                .iter()
                .map(|s| {
                    let t = s.split(" ").collect::<Vec<&str>>();
                    let amt: i32 = t[0].parse().unwrap();
                    let color_str = t[1];
                    let color = Color::new(amt, color_str);
                    color
                })
                .collect();
            acc.push(set_colors);
            acc
        });
        let mut possible = true;
        for s in set {
            for x in s {
                if !is_possible(&x) {
                    possible = false;
                    break;
                }
            }
            if !possible {
                break;
            }
        }
        if possible {
            acc += game;
        }
        acc
    });
    return res;
}

pub fn part_two(input: &str) -> i32 {
    let res = input.lines().fold(0, |acc, l| {
        let split = l.split(": ").into_iter().collect::<Vec<&str>>();
        let contents = split[1];
        let set_strs = contents.split("; ").collect::<Vec<&str>>();
        let set = set_strs.iter().fold(vec![], |mut acc, s| {
            let set_colors_inp = s.split(", ").collect::<Vec<&str>>();
            let set_colors: Vec<Color> = set_colors_inp
                .iter()
                .map(|s| {
                    let t = s.split(" ").collect::<Vec<&str>>();
                    let amt: i32 = t[0].parse().unwrap();
                    let color_str = t[1];
                    let color = Color::new(amt, color_str);
                    color
                })
                .collect();
            acc.push(set_colors);
            acc
        });
        let mut green: Vec<i32> = Vec::new();
        let mut blue: Vec<i32> = Vec::new();
        let mut red: Vec<i32> = Vec::new();
        for s in set {
            for x in s {
                match x {
                    Color::Blue(val) => blue.push(val),
                    Color::Red(val) => red.push(val),
                    Color::Green(val) => green.push(val),
                }
            }
        }
        let green_amt = green.iter().max().unwrap();
        let blue_amt = blue.iter().max().unwrap();
        let red_amt = red.iter().max().unwrap();
        let num = green_amt * blue_amt * red_amt;
        acc + num
    });
    return res;
}

#[cfg(test)]
mod test {
    use crate::day2::part_two;

    use super::part_one;

    #[test]
    fn test_part_one() {
        let input = r#"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"#;
        let res = part_one(input);
        assert_eq!(res, 8);
    }

    #[test]
    fn test_part_two() {
        let input = r#"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"#;
        let res = part_two(input);
        assert_eq!(res, 2286);
    }
}
