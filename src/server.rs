use wayland_sys::*;

pub struct Server {
    display: *mut server::wl_display,
    client: *mut server::wl_client,
    event_loop: *mut server::wl_event_loop
}

impl Server {
    pub fn new() -> Self {
        unsafe {
            // Create wayland display and client.
            let display = server::wl_display_create();
            if display.is_null() {
                println!("display not made."); // TODO: Fix to error!().
                std::process::exit(-1);
            }

            let client = server::wl_client_create(display, 0);
            if client.is_null() {
                println!("client not made."); // TODO: Fix to error!().
                //std::process::exit(-1);
            }

            let event_loop = server::wl_event_loop_create();

            if server::wl_display_init_shm(display) == -1 {
                println!("wl_display_init_shm failed!");
            }

            Server {
                display,
                client,
                event_loop
            }
        }
    }

    pub fn disconnect(&self) {
        unsafe {
            // Destroy objects.
            server::wl_client_destroy(self.client);
            server::wl_display_destroy(self.display);

            // If the event loop has existing sources, those cannot be safely removed afterwards.
            // Therefore one must call wl_event_source_remove() on all event sources before destroying the event loop context.
            //server::wl_event_source_remove();
            server::wl_event_loop_destroy(self.event_loop);
        }
    }

    pub fn run(&self) {
        println!("Run");
        unsafe {
            loop {
                if server::wl_event_loop_dispatch(self.event_loop, 50) == -1 { // -1 for polling (or timer update) error.

                    println!("-1 for polling (or timer update) error.")

                } else { // 0 for success

                    println!("0 for success");

                }
            }
        }
    }
}