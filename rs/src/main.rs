
pub mod reader;
pub mod day1;

fn main() -> Result<(), std::io::Error> {
    let input = reader::read(None)?;
    day1::part_two(&input);
    Ok(())
}
