#pragma once

extern "C" {
    #include <wayland-client.h>
}

class MBDisplay {

private:
    MBDisplay();
    static MBDisplay *_instance;
    static wl_display *_display;

public:
    static MBDisplay *getInstance();

    void dispatch();
    void roundtrip();

    wl_registry *generateRegistry();

};
