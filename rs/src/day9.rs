pub fn part_one(input: &str) -> i32 {
    let mut res = 0;
    let lines = input.lines();
    for line in lines {
        let nums = get_nums(line);
        let mut difs = get_difs(&nums);
        let num_to_add_to = nums.last().unwrap();
        let mut num_to_add = 0;
        difs.reverse();
        for d in difs {
            let c = d.last().unwrap();
            num_to_add += c;
        }
        res += num_to_add_to + num_to_add;
    }
    res
}

pub fn part_two(input: &str) -> i32 {
    let mut res = 0;
    let lines = input.lines();
    for line in lines {
        let nums = get_nums(line);
        let mut difs = get_difs(&nums);
        let num_to_subtract_from = nums.first().unwrap();
        let mut num_to_subtract = 0;
        difs.reverse();
        for d in difs {
            let c = d.first().unwrap();
            num_to_subtract = c - num_to_subtract;
        }
        let x = num_to_subtract_from - num_to_subtract;
        res += x;
    }
    res
}

fn get_nums(line: &str) -> Vec<i32> {
    line.split(' ').map(|s| s.parse().unwrap()).collect()
}

fn get_difs(nums: &Vec<i32>) -> Vec<Vec<i32>> {
    let mut res = Vec::new();
    let mut cur_nums = nums.clone();
    loop {
        let difs = get_cur_difs(&cur_nums);
        let mut s = std::collections::HashSet::new();
        for d in difs.clone() {
            s.insert(d);
        }
        cur_nums = difs.clone();
        res.push(difs);
        if s.len() == 1 {
            break;
        }
    }
    res
}

fn get_cur_difs(nums: &Vec<i32>) -> Vec<i32> {
    let mut res = Vec::new();
    for i in 1..nums.len() {
        let cur = nums[i];
        let prev = nums[i - 1];
        let n = cur - prev;
        res.push(n);
    }
    res
}
