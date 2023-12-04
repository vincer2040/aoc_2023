pub mod reader;
pub mod day1;
pub mod day2;
pub mod day3;
pub mod day4;

fn main() -> Result<(), std::io::Error> {
    let input = reader::read(None)?;
    let res = day4::part_two(&input);
    println!("{}", res);
    Ok(())
}
