
/// # A great Desktop Environment (DE) built by Kreimben.

use log::*;

mod server;

#[cfg(target_os = "linux")]
fn main() {

    trace!("MagicBox!");

    if am_i_root() {

        logic();

    } else {
        error!("You have to run MagicBox with root privileges.");
        std::process::exit(-1);
    }
}

fn logic() {

    let server = server::Server::new();

    server.run();

    //server.disconnect();
}

#[inline]
fn am_i_root() -> bool {
    unsafe {
        let uid = libc::getuid();

        if uid != 0 {
            return false;
        } else {
            return true;
        }
    };
}
