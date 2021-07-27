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
    // static MBApp *_instance;

    xcb_connection_t *connect;
    xcb_screen_t     *screen;
    xcb_window_t      window_id;
    uint32_t          propName;
    uint32_t         *props;


public:
    // static MBApp &shared() {
    //     if (_instance == 0) _instance = new MBApp();
    //     return *_instance;
    // }

    MBApp();

    static void printScreenInfo(xcb_screen_t *screen);

    void eventLoop();
    void disconnectApp();
};


#endif //MAGICBOXWM_MBAPP_H
