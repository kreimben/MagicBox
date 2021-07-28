#ifndef MBTOPBAR_H_
#define MBTOPBAR_H_

#include <xcb/xcb.h>
#include <memory>

class MBTopBar {

private:
    xcb_window_t topbarWindowID;
    void eventLoop();

    xcb_connection_t *connect;
    xcb_screen_t *screen;

public:
    MBTopBar(xcb_connection_t *connect, xcb_screen_t *screen, xcb_window_t rootWindowID);

    xcb_window_t getTopbarWindowID();

};

#endif // MBTOPBAR_H_
