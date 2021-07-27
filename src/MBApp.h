//
// Created by ubuntu on 7/27/21.
//

#ifndef MAGICBOXWM_MBAPP_H
#define MAGICBOXWM_MBAPP_H

#include <iostream>
#include <memory>
#include <xcb/xcb.h>

class MBApp {

private:
    xcb_connection_t *connect;
    xcb_screen_t     *screen;
    xcb_window_t      window_id;
    uint32_t          propName;
    uint32_t         *props;


public:
    MBApp();

    static void printScreenInfo(xcb_screen_t *screen);

    void eventLoop();
    void disconnectApp();
};


#endif //MAGICBOXWM_MBAPP_H
