//
// Created by ubuntu on 7/27/21.
//

#ifndef MAGICBOXWM_MBAPP_H
#define MAGICBOXWM_MBAPP_H

#include <iostream>
#include <memory>

#include <wayland-client-core.h>

class MBApp {

private:
    MBApp();
    ~MBApp();
    static MBApp* _instance;

    wl_display* display;

public:
    static MBApp* getInstance();
};


#endif //MAGICBOXWM_MBAPP_H
