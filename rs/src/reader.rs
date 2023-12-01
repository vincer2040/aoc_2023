use std::io::Read;

pub fn read(path: Option<&str>) -> Result<String, std::io::Error> {
    match path {
        Some(p) => std::fs::read_to_string(p),
        None => {
            let mut res = String::new();
            std::io::stdin().read_to_string(&mut res)?;
            Ok(res)
        }
    }
}
