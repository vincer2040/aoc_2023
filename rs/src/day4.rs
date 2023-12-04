pub fn part_one(input: &str) -> u32 {
    let mut res = 0;
    input.lines().for_each(|l| {
        let game: Vec<&str> = l.split(": ").collect::<Vec<&str>>()[1]
            .split(" | ")
            .collect();
        let winnums = game[0]
            .split(' ')
            .filter(|s| *s != " " && *s != "")
            .map(|n| n.trim().parse().unwrap())
            .collect::<std::collections::HashSet<u32>>();
        let gotnums = game[1]
            .split(' ')
            .filter(|s| *s != " " && *s != "")
            .map(|n| n.trim().parse().unwrap())
            .collect::<std::collections::HashSet<u32>>();
        let winning = winnums.intersection(&gotnums).collect::<Vec<&u32>>();
        if winning.len() > 0 {
            res += u32::pow(2, (winning.len() as u32) - 1);
        }
    });
    res
}

pub fn part_two(input: &str) -> u32 {
    let lines = input.lines();
    let lines_len = lines.clone().count();
    let mut played = vec![0; lines_len];
    lines.enumerate().for_each(|(i, l)| {
        played[i] += 1;
        let game: Vec<&str> = l.split(": ").collect::<Vec<&str>>()[1]
            .split(" | ")
            .collect();
        let winnums = game[0]
            .split(' ')
            .filter(|s| *s != " " && *s != "")
            .map(|n| n.trim().parse().unwrap())
            .collect::<std::collections::HashSet<u32>>();
        let gotnums = game[1]
            .split(' ')
            .filter(|s| *s != " " && *s != "")
            .map(|n| n.trim().parse().unwrap())
            .collect::<std::collections::HashSet<u32>>();
        let winning = winnums.intersection(&gotnums).collect::<Vec<&u32>>();
        for w in 0..winning.len() {
            played[w + i + 1] += played[i];
        }
    });
    played.iter().sum::<u32>()
}
