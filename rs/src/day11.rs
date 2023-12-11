pub fn part_one(input: &str) -> u64 {
    solve(input, 1)
}

pub fn part_two(input: &str) -> u64 {
    solve(input, 1_000_000)
}

fn solve(input: &str, num_times: u64) -> u64 {
    let mut res = 0;
    let mut galaxies = find_galaxies(input);
    let row_exps = row_expansions(input);
    let col_exps = col_expansions(input);

    let len = galaxies.len();

    for i in 0..len {
        let (y, x) = galaxies[i];
        let new_y: u64;
        let new_x: u64;
        let row_exp = row_exps[y as usize];
        let col_exp = col_exps[x as usize];
        if num_times == 1 {
            new_y = y + row_exp;
            new_x = x + col_exp;
        } else {
            new_y = y + (row_exp * (num_times - 1));
            new_x = x + (col_exp * (num_times - 1));
        }
        galaxies[i] = (new_y, new_x);
    }

    for i in 0..len {
        let mut c = 0;
        let (y, x) = galaxies[i];
        for j in (i + 1)..len {
            let (yi, xi) = galaxies[j];
            let d = dist((y, x), (yi, xi));
            c += d;
        }
        res += c;
    }
    res
}

fn row_expansions(input: &str) -> Vec<u64> {
    let mut res = Vec::new();
    let mut num_expansions = 0;
    for line in input.lines() {
        let mut s = std::collections::HashSet::new();
        for ch in line.chars() {
            s.insert(ch);
        }
        if s.len() == 1 {
            num_expansions += 1;
        }
        res.push(num_expansions);
    }
    res
}

fn col_expansions(input: &str) -> Vec<u64> {
    let mut res = Vec::new();
    let mut num_expansions = 0;
    let lines: Vec<&str> = input.lines().collect();
    let line_len = lines[0].len();
    for i in 0..line_len {
        let mut set = std::collections::HashSet::new();
        for line in lines.iter() {
            let ch = line.as_bytes()[i] as char;
            set.insert(ch);
        }
        if set.len() == 1 {
            num_expansions += 1;
        }
        res.push(num_expansions);
    }
    res
}

fn find_galaxies(input: &str) -> Vec<(u64, u64)> {
    let mut res = Vec::new();
    let lines = input.lines();
    for (i, line) in lines.enumerate() {
        for (j, ch) in line.chars().enumerate() {
            if ch == '#' {
                let p = (i as u64, j as u64);
                res.push(p);
            }
        }
    }
    res
}

fn dist((y1, x1): (u64, u64), (y2, x2): (u64, u64)) -> u64 {
    let y: u64 = ((y2 as i64 - y1 as i64) as i64).abs() as u64;
    let x: u64 = ((x2 as i64 - x1 as i64) as i64).abs() as u64;
    y + x
}
