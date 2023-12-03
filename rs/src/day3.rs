pub fn part_one(input: &str) -> i32 {
    let mut res = 0;
    let matrix = make_matrix(input);
    let matrix_len = matrix.len();
    for (line_num, row) in matrix.iter().enumerate() {
        let row_len = row.len();
        let mut i = 0;
        let mut nums: Vec<i32> = Vec::new();
        while i < row_len {
            let ch = row[i];
            if is_digit(ch) {
                let mut num = 0;
                let mut valid = false;
                while i < row_len && is_digit(row[i]) {
                    num = (num * 10) + (row[i] as i32 - '0' as i32);
                    if !valid {
                        valid = is_valid(&matrix, matrix_len, row_len, line_num, i);
                    }
                    i += 1;
                }
                if valid {
                    nums.push(num);
                }
            }
            i += 1;
        }
        nums.iter().for_each(|num| {
            res += num;
        });
    }
    res
}

#[derive(Debug, Hash, PartialEq, Eq)]
struct GearIdx {
    y: usize,
    x: usize,
}

pub fn part_two(input: &str) -> i32 {
    let mut res = 0;
    let matrix = make_matrix(input);
    let matrix_len = matrix.len();
    let mut map: std::collections::HashMap<GearIdx, Vec<i32>> = std::collections::HashMap::new();
    for (line_num, row) in matrix.iter().enumerate() {
        let row_len = row.len();
        let mut i = 0;
        while i < row_len {
            let ch = row[i];
            if is_digit(ch) {
                let mut num = 0;
                let mut possible_gear_part = (false, 0, 0);
                while i < row_len && is_digit(row[i]) {
                    num = (num * 10) + (row[i] as i32 - '0' as i32);
                    if !possible_gear_part.0 {
                        possible_gear_part =
                            is_gear_part(&matrix, matrix_len, row_len, line_num, i);
                    }
                    i += 1;
                }
                if possible_gear_part.0 {
                    let idx = GearIdx {
                        y: possible_gear_part.1,
                        x: possible_gear_part.2,
                    };
                    match map.get_mut(&idx) {
                        Some(val) => {
                            val.push(num);
                        }
                        None => {
                            map.insert(idx, vec![num]);
                        }
                    }
                }
            }
            i += 1;
        }
    }
    map.values().for_each(|val| {
        if val.len() == 2 {
            let ratio = val[0] * val[1];
            res += ratio;
        }
    });
    res
}

fn make_matrix(input: &str) -> Vec<Vec<char>> {
    let mut res = Vec::new();
    input.lines().for_each(|l| {
        let mut row = Vec::new();
        l.chars().for_each(|ch| {
            row.push(ch);
        });
        res.push(row);
    });
    res
}

fn is_digit(ch: char) -> bool {
    '0' <= ch && ch <= '9'
}

fn is_special(ch: char) -> bool {
    ch == '*'
        || ch == '#'
        || ch == '+'
        || ch == '$'
        || ch == '@'
        || ch == '%'
        || ch == '&'
        || ch == '/'
        || ch == '-'
        || ch == '='
}

fn is_gear_symbol(ch: char) -> bool {
    ch == '*'
}

fn is_gear_part(
    matrix: &Vec<Vec<char>>,
    len: usize,
    row_len: usize,
    row: usize,
    row_pos: usize,
) -> (bool, usize, usize) {
    if row == 0 {
        if row_pos == 0 {
            let right = matrix[0][row_pos + 1];
            if is_gear_symbol(right) {
                return (true, 0, row_pos + 1);
            }
            let down = matrix[1][row_pos];
            if is_gear_symbol(down) {
                return (true, 1, row_pos);
            }
            let down_right = matrix[1][row_pos + 1];
            if is_gear_symbol(down_right) {
                return (true, 1, row_pos + 1);
            }
            return (false, 0, 0);
        }
        if row_pos == row_len - 1 {
            let left = matrix[0][row_pos - 1];
            if is_gear_symbol(left) {
                return (true, 0, row_pos - 1);
            }
            let down = matrix[1][row_pos];
            if is_gear_symbol(down) {
                return (true, 1, row_pos);
            }
            let down_left = matrix[1][row_pos - 1];
            if is_gear_symbol(down_left) {
                return (true, 1, row_pos - 1);
            }
            return (false, 0, 0);
        }
        let right = matrix[0][row_pos + 1];
        if is_gear_symbol(right) {
            return (true, 0, row_pos + 1);
        }
        let left = matrix[0][row_pos - 1];
        if is_gear_symbol(left) {
            return (true, 0, row_pos - 1);
        }
        let down_left = matrix[1][row_pos - 1];
        if is_gear_symbol(down_left) {
            return (true, 1, row_pos - 1);
        }
        let down = matrix[1][row_pos];
        if is_gear_symbol(down) {
            return (true, 1, row_pos);
        }
        let down_right = matrix[1][row_pos + 1];
        if is_gear_symbol(down_right) {
            return (true, 1, row_pos + 1);
        }
        return (false, 0, 0);
    }
    if row == len - 1 {
        if row_pos == 0 {
            let right = matrix[row][row_pos + 1];
            if is_gear_symbol(right) {
                return (true, row, row_pos + 1);
            }
            let up = matrix[row - 1][row_pos];
            if is_gear_symbol(up) {
                return (true, row - 1, row_pos);
            }
            let up_right = matrix[row - 1][row_pos + 1];
            if is_gear_symbol(up_right) {
                return (true, row - 1, row_pos + 1);
            }
            return (false, 0, 0);
        }
        if row_pos == row_len - 1 {
            let left = matrix[row][row_pos - 1];
            if is_gear_symbol(left) {
                return (true, row, row_pos - 1);
            }
            let up = matrix[row - 1][row_pos];
            if is_gear_symbol(up) {
                return (true, row - 1, row_pos);
            }
            let up_left = matrix[row - 1][row_pos - 1];
            if is_gear_symbol(up_left) {
                return (true, row - 1, row_pos - 1);
            }
            return (false, 0, 0);
        }
        let left = matrix[row][row_pos - 1];
        if is_gear_symbol(left) {
            return (true, row, row_pos - 1);
        }
        let right = matrix[row][row_pos + 1];
        if is_gear_symbol(right) {
            return (true, row, row_pos + 1);
        }
        let up_left = matrix[row - 1][row_pos - 1];
        if is_gear_symbol(up_left) {
            return (true, row - 1, row_pos - 1);
        }
        let up = matrix[row - 1][row_pos];
        if is_gear_symbol(up) {
            return (true, row - 1, row_pos);
        }
        let up_right = matrix[row - 1][row_pos + 1];
        if is_gear_symbol(up_right) {
            return (true, row - 1, row_pos + 1);
        }
        return (false, 0, 0);
    }

    if row_pos == 0 {
        let right = matrix[row][row_pos + 1];
        if is_gear_symbol(right) {
            return (true, row, row_pos + 1);
        }
        let up = matrix[row - 1][row_pos];
        if is_gear_symbol(up) {
            return (true, row - 1, row_pos);
        }
        let up_right = matrix[row - 1][row_pos + 1];
        if is_gear_symbol(up_right) {
            return (true, row - 1, row_pos + 1);
        }
        let down = matrix[row + 1][row_pos];
        if is_gear_symbol(down) {
            return (true, row + 1, row_pos);
        }
        let down_right = matrix[row + 1][row_pos + 1];
        if is_gear_symbol(down_right) {
            return (true, row + 1, row_pos + 1);
        }
        return (false, 0, 0);
    }

    if row_pos == row_len - 1 {
        let left = matrix[row][row_pos - 1];
        if is_gear_symbol(left) {
            return (true, row, row_pos - 1);
        }
        let up = matrix[row - 1][row_pos];
        if is_gear_symbol(up) {
            return (true, row - 1, row_pos);
        }
        let up_left = matrix[row - 1][row_pos - 1];
        if is_gear_symbol(up_left) {
            return (true, row - 1, row_pos - 1);
        }
        let down = matrix[row + 1][row_pos];
        if is_gear_symbol(down) {
            return (true, row + 1, row_pos);
        }
        let down_left = matrix[row + 1][row_pos - 1];
        if is_gear_symbol(down_left) {
            return (true, row + 1, row_pos - 1);
        }
        return (false, 0, 0);
    }

    let right = matrix[row][row_pos + 1];
    if is_gear_symbol(right) {
        return (true, row, row_pos + 1);
    }
    let left = matrix[row][row_pos - 1];
    if is_gear_symbol(left) {
        return (true, row, row_pos - 1);
    }
    let up_left = matrix[row - 1][row_pos - 1];
    if is_gear_symbol(up_left) {
        return (true, row - 1, row_pos - 1);
    }
    let up = matrix[row - 1][row_pos];
    if is_gear_symbol(up) {
        return (true, row - 1, row_pos);
    }
    let up_right = matrix[row - 1][row_pos + 1];
    if is_gear_symbol(up_right) {
        return (true, row - 1, row_pos + 1);
    }
    let down_right = matrix[row + 1][row_pos + 1];
    if is_gear_symbol(down_right) {
        return (true, row + 1, row_pos + 1);
    }
    let down = matrix[row + 1][row_pos];
    if is_gear_symbol(down) {
        return (true, row + 1, row_pos);
    }
    let down_left = matrix[row + 1][row_pos - 1];
    if is_gear_symbol(down_left) {
        return (true, row + 1, row_pos - 1);
    }
    return (false, 0, 0);
}

fn is_valid(
    matrix: &Vec<Vec<char>>,
    len: usize,
    row_len: usize,
    row: usize,
    row_pos: usize,
) -> bool {
    if row == 0 {
        if row_pos == 0 {
            let right = matrix[0][row_pos + 1];
            let down = matrix[1][row_pos];
            let down_right = matrix[1][row_pos + 1];
            return is_special(right) || is_special(down) || is_special(down_right);
        }
        if row_pos == row_len - 1 {
            let left = matrix[0][row_pos - 1];
            let down = matrix[1][row_pos];
            let down_left = matrix[1][row_pos - 1];
            return is_special(left) || is_special(down) || is_special(down_left);
        }
        let right = matrix[0][row_pos + 1];
        let left = matrix[0][row_pos - 1];
        let down_left = matrix[1][row_pos - 1];
        let down = matrix[1][row_pos];
        let down_right = matrix[1][row_pos + 1];
        return is_special(right)
            || is_special(left)
            || is_special(down_left)
            || is_special(down)
            || is_special(down_right);
    }
    if row == len - 1 {
        if row_pos == 0 {
            let right = matrix[row][row_pos + 1];
            let up = matrix[row - 1][row_pos];
            let up_right = matrix[row - 1][row_pos + 1];
            return is_special(right) || is_special(up) || is_special(up_right);
        }
        if row_pos == row_len - 1 {
            let left = matrix[row][row_pos - 1];
            let up = matrix[row - 1][row_pos];
            let up_left = matrix[row - 1][row_pos - 1];
            return is_special(left) || is_special(up) || is_special(up_left);
        }
        let left = matrix[row][row_pos - 1];
        let right = matrix[row][row_pos + 1];
        let up_left = matrix[row - 1][row_pos - 1];
        let up = matrix[row - 1][row_pos];
        let up_right = matrix[row - 1][row_pos + 1];
        return is_special(left)
            || is_special(right)
            || is_special(up_left)
            || is_special(up)
            || is_special(up_right);
    }

    if row_pos == 0 {
        let right = matrix[row][row_pos + 1];
        let up = matrix[row - 1][row_pos];
        let up_right = matrix[row - 1][row_pos + 1];
        let down = matrix[row + 1][row_pos];
        let down_right = matrix[row + 1][row_pos + 1];
        return is_special(right)
            || is_special(up)
            || is_special(up_right)
            || is_special(down)
            || is_special(down_right);
    }

    if row_pos == row_len - 1 {
        let left = matrix[row][row_pos - 1];
        let up = matrix[row - 1][row_pos];
        let up_left = matrix[row - 1][row_pos - 1];
        let down = matrix[row + 1][row_pos];
        let down_left = matrix[row + 1][row_pos - 1];
        return is_special(left)
            || is_special(up)
            || is_special(up_left)
            || is_special(down)
            || is_special(down_left);
    }

    let right = matrix[row][row_pos + 1];
    let left = matrix[row][row_pos - 1];
    let up_left = matrix[row - 1][row_pos - 1];
    let up = matrix[row - 1][row_pos];
    let up_right = matrix[row - 1][row_pos + 1];
    let down_right = matrix[row + 1][row_pos + 1];
    let down = matrix[row + 1][row_pos];
    let down_left = matrix[row + 1][row_pos - 1];

    return is_special(right)
        || is_special(left)
        || is_special(up_left)
        || is_special(up)
        || is_special(up_right)
        || is_special(down_right)
        || is_special(down)
        || is_special(down_left);
}

#[cfg(test)]
mod test {
    use super::{part_one, part_two};

    #[test]
    fn part_one_test() {
        let input = r#"467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598.."#;
        let res = part_one(input);
        assert_eq!(res, 4361);
    }

    #[test]
    fn part_two_test() {
        let input = r#"467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598.."#;
        let res = part_two(input);
        assert_eq!(res, 467835);
    }
}
