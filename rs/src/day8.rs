pub fn part_one(input: &str) -> i32 {
    let mut split = input.split("\n\n");
    let instructions = split.nth(0).unwrap();
    let map = split.nth(0).unwrap().split("\n").filter(|l| *l != "");
    let mut graph: std::collections::HashMap<&str, (String, String)> =
        std::collections::HashMap::new();
    for row in map {
        let mut from_to = row.split(" = ");
        let from = from_to.nth(0).unwrap();
        let mut left_right = from_to.nth(0).unwrap().split(", ");
        let left = left_right.nth(0).unwrap().replace('(', "");
        let right = left_right.nth(0).unwrap().replace(')', "");
        graph.insert(from, (left, right));
    }
    return walk(&graph, "AAA", instructions);
}

pub fn part_two(input: &str) -> u64 {
    let mut split = input.split("\n\n");
    let instructions = split.nth(0).unwrap();
    let map = split.nth(0).unwrap().split("\n").filter(|l| *l != "");
    let mut graph: std::collections::HashMap<&str, (String, String)> =
        std::collections::HashMap::new();
    for row in map {
        let mut from_to = row.split(" = ");
        let from = from_to.nth(0).unwrap();
        let mut left_right = from_to.nth(0).unwrap().split(", ");
        let left = left_right.nth(0).unwrap().replace('(', "");
        let right = left_right.nth(0).unwrap().replace(')', "");
        graph.insert(from, (left, right));
    }

    let mut lens = Vec::new();

    for key in graph.keys() {
        if !key.ends_with('A') {
            continue;
        }

        let p = walk2(&graph, key, instructions);
        lens.push(p);
    }
    return lcm_of_vec(&lens);
}

fn walk(
    graph: &std::collections::HashMap<&str, (String, String)>,
    cur_location: &str,
    instructions_str: &str,
) -> i32 {
    let mut cur = cur_location.to_owned();
    let mut instruction_idx = 0;
    let instructions = instructions_str.as_bytes();
    let mut num_steps = 0;
    while cur != "ZZZ" {
        let left_right = graph.get(cur.as_str()).unwrap();
        let instruction = instructions[instruction_idx % instructions.len()];
        if instruction == b'L' {
            cur = left_right.0.clone();
        } else {
            cur = left_right.1.clone();
        }
        num_steps += 1;
        instruction_idx += 1;
    }
    return num_steps;
}

fn walk2(
    graph: &std::collections::HashMap<&str, (String, String)>,
    cur_location: &str,
    instructions_str: &str,
) -> u64 {
    let mut cur = cur_location.to_owned();
    let mut instruction_idx = 0;
    let mut num_steps = 0;
    let instructions = instructions_str.as_bytes();
    while !cur.ends_with('Z') {
        let (left, right) = graph.get(cur.as_str()).unwrap();
        let instruction = instructions[instruction_idx % instructions.len()];
        if instruction == b'L' {
            cur = left.clone();
        } else {
            cur = right.clone();
        }
        num_steps += 1;
        instruction_idx += 1;
    }
    return num_steps;
}

fn gcd(a: u64, b: u64) -> u64 {
    if b == 0 {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

fn lcm(a: u64, b: u64) -> u64 {
    return (a * b) / gcd(a, b);
}

fn lcm_of_vec(v: &Vec<u64>) -> u64 {
    let mut result = v[0];
    for i in 1..v.len() {
        result = lcm(result, v[i]);
    }
    return result;
}
