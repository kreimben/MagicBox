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
    std::shared_ptr<xcb_connection_t> connect;
    std::shared_ptr<xcb_screen_t> screen;
    xcb_window_t      window_id;
    uint32_t          propName;
    uint32_t         *props;

    MBApp();
    static MBApp *_instance;

public:
    static MBApp *getInstance();

    static void printScreenInfo(std::shared_ptr<xcb_screen_t> screen);

    void eventLoop();
    void disconnectApp();

    std::shared_ptr<xcb_connection_t> getConnection();
    xcb_window_t getWindowID();
    std::shared_ptr<xcb_screen_t> getScreen();
};


#endif //MAGICBOXWM_MBAPP_H
