#[derive(Debug)]
struct MapItem {
    dst: i64,
    src: i64,
    range: i64,
}

#[derive(Debug)]
enum LineData {
    Seeds(Vec<i64>),
    Chunk(Vec<MapItem>),
}

pub fn part_one(input: &str) -> i64 {
    let parsed: Vec<LineData> = input.split("\n\n").map(parse_line).collect();
    let seeds = match &parsed[0] {
        LineData::Seeds(s) => s,
        _ => unreachable!(),
    };
    let chunks = &parsed[1..].iter().fold(vec![], |mut acc, item| {
        match item {
            LineData::Chunk(c) => acc.push(c),
            _ => unreachable!(),
        }
        acc
    });

    let mut end = Vec::new();

    for s in seeds {
        let mut seed = *s;
        for chunk in chunks {
            for check in *chunk {
                if seed >= check.src && seed <= check.src + check.range {
                    seed += check.dst - check.src;
                    break;
                }
            }
        }
        end.push(seed);
    }
    *end.iter().min().unwrap()
}

pub fn part_two(input: &str) -> i64 {
    let parsed: Vec<LineData> = input.split("\n\n").map(parse_line).collect();
    let seeds = match &parsed[0] {
        LineData::Seeds(s) => s,
        _ => unreachable!(),
    };
    let chunks = &parsed[1..].iter().fold(vec![], |mut acc, item| {
        match item {
            LineData::Chunk(c) => acc.push(c),
            _ => unreachable!(),
        }
        acc
    });

    let mut end = Vec::new();

    let mut start = 0;
    let mut is_range = false;

    for s in seeds {
        if !is_range {
            start = *s;
            is_range = true;
            continue;
        } else {
            let end_num = start + *s - 1;
            for i in start..end_num {
                let mut seed = i;
                for chunk in chunks {
                    for check in *chunk {
                        if seed >= check.src && seed <= check.src + check.range {
                            seed += check.dst - check.src;
                            break;
                        }
                    }
                }
                end.push(seed);
            }
            is_range = false;
        }
    }
    *end.iter().min().unwrap()
}

fn parse_line(line: &str) -> LineData {
    if line.starts_with("seeds:") {
        let nums: Vec<i64> = line
            .replace("seeds: ", "")
            .split(" ")
            .map(|n| n.parse().unwrap())
            .collect();
        return LineData::Seeds(nums);
    } else if line.starts_with("seed-to-soil") {
        let map: Vec<MapItem> = line
            .replace("seed-to-soil map:", "")
            .lines()
            .filter(|l| *l != "")
            .map(parse_nums)
            .collect();
        return LineData::Chunk(map);
    } else if line.starts_with("soil-to-fertilizer") {
        let map: Vec<MapItem> = line
            .replace("soil-to-fertilizer map:", "")
            .lines()
            .filter(|l| *l != "")
            .map(parse_nums)
            .collect();
        return LineData::Chunk(map);
    } else if line.starts_with("fertilizer-to-water") {
        let map: Vec<MapItem> = line
            .replace("fertilizer-to-water map:", "")
            .lines()
            .filter(|l| *l != "")
            .map(parse_nums)
            .collect();
        return LineData::Chunk(map);
    } else if line.starts_with("water-to-light") {
        let map: Vec<MapItem> = line
            .replace("water-to-light map:", "")
            .lines()
            .filter(|l| *l != "")
            .map(parse_nums)
            .collect();
        return LineData::Chunk(map);
    } else if line.starts_with("light-to-temperature") {
        let map: Vec<MapItem> = line
            .replace("light-to-temperature map:", "")
            .lines()
            .filter(|l| *l != "")
            .map(parse_nums)
            .collect();
        return LineData::Chunk(map);
    } else if line.starts_with("temperature-to-humidity") {
        let map: Vec<MapItem> = line
            .replace("temperature-to-humidity map:", "")
            .lines()
            .filter(|l| *l != "")
            .map(parse_nums)
            .collect();
        return LineData::Chunk(map);
    } else if line.starts_with("humidity-to-location") {
        let map: Vec<MapItem> = line
            .replace("humidity-to-location map:", "")
            .lines()
            .filter(|l| *l != "")
            .map(parse_nums)
            .collect();
        return LineData::Chunk(map);
    } else {
        unreachable!()
    }
}

fn parse_nums(l: &str) -> MapItem {
    let nums: Vec<i64> = l.split(" ").map(|n| n.parse().unwrap()).collect();
    MapItem {
        dst: nums[0],
        src: nums[1],
        range: nums[2],
    }
}
