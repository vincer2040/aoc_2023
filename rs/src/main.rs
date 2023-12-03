pub mod reader;
pub mod day1;
pub mod day2;
pub mod day3;

fn main() -> Result<(), std::io::Error> {
    let input = reader::read(None)?;
    let res = day3::part_two(&input);
    println!("{}", res);
    Ok(())
}
