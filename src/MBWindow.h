//
// Created by ubuntu on 7/27/21.
//
// This class is just primitive class for inheritances.
//

#ifndef MAGICBOXWM_MBWINDOW_H
#define MAGICBOXWM_MBWINDOW_H

#include <xcb/xcb.h>

class MBWindow {

private:

public:
    MBWindow(xcb_connection_t *connect, xcb_screen_t *screen, xcb_window_t rootWindowID);
    xcb_window_t window_id;
};


#endif //MAGICBOXWM_MBWINDOW_H
