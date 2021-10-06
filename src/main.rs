fn main() {
    let my_name = String::from("Kreimben");
    let my_glass = Glass::new(&my_name);

    println!("My glass is valid: {}", &my_glass.breaked(&my_glass));
    println!("And my owner is: {}", &my_glass.owner);

    my_glass.get_info();
}

struct Glass {
    owner: String,
    is_valid: bool,
}

trait Fungiable {
    fn breaked<T: Fungiable>(&self, _option: &T) -> bool;
    fn new(owner: &str) -> Self;
    fn get_info(&self);
}

impl Fungiable for Glass {
    fn breaked<T: Fungiable>(&self, _option: &T) -> bool {
        self.is_valid
    }

    fn new(owner: &str) -> Self {
        Glass {
            owner: owner.to_string(),
            is_valid: !owner.is_empty(),
        }
    }

    fn get_info(&self) {
        let current_time = chrono::Utc::now();
        let current_os = consts::OS;

        println!("Current time is {}.", current_time);

        let os_info = current_os;
        println!("OS: {}", os_info);
    }
}

use std::env::consts;
