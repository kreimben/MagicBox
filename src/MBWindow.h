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
    xcb_window_t window_id;

public:
    MBWindow()
};


#endif //MAGICBOXWM_MBWINDOW_H
