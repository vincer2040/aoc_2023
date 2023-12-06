use std::ops::BitXor;

pub fn part_one(input: &str) -> usize {
    let mut lines = input.lines();
    let times: Vec<usize> = lines
        .nth(0)
        .unwrap()
        .replace("Time: ", "")
        .split(' ')
        .filter(|s| *s != "")
        .map(|s| s.parse().unwrap())
        .collect();
    let distances: Vec<usize> = lines
        .nth(0)
        .unwrap()
        .replace("Distance: ", "")
        .split(' ')
        .filter(|s| *s != "")
        .map(|s| s.parse().unwrap())
        .collect();

    let mut res = 1;
    for (i, time) in times.iter().enumerate() {
        let dist = distances[i];
        let possible = get_possible_ways_to_win(*time, dist);
        res *= possible;
    }
    res
}

pub fn part_two(input: &str) -> usize {
    let mut lines = input.lines();
    let time: usize = lines
        .nth(0)
        .unwrap()
        .replace("Time: ", "")
        .split(' ')
        .filter(|s| *s != "")
        .fold(String::new(), |acc, s| acc.to_owned() + s)
        .parse()
        .unwrap();
    let dist: usize = lines
        .nth(0)
        .unwrap()
        .replace("Distance: ", "")
        .split(' ')
        .filter(|s| *s != "")
        .fold(String::new(), |acc, s| acc.to_owned() + s)
        .parse()
        .unwrap();
    get_possible_ways_to_win(time, dist)
}

fn get_possible_ways_to_win(time: usize, dist: usize) -> usize {
    let d = time * time - 4 * dist;
    let sqrt_d = (d as f64).sqrt() as usize;
    if sqrt_d * sqrt_d == d {
        sqrt_d - 1
    } else {
        sqrt_d + 1 - (time & 1).bitxor(sqrt_d & 1)
    }
}
