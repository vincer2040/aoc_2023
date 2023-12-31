pub mod day1;
pub mod day11;
pub mod day2;
pub mod day3;
pub mod day4;
pub mod day5;
pub mod day6;
pub mod day7;
pub mod day8;
pub mod day9;
pub mod reader;

fn main() -> Result<(), std::io::Error> {
    let input = reader::read(None)?;
    let res = day11::part_two(&input);
    println!("{}", res);
    Ok(())
}
