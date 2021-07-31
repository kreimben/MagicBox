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
    static std::unique_ptr<MBApp> _instance;

    std::unique_ptr<wl_display> display;

public:
    MBApp();
    static std::unique_ptr<MBApp>& getInstance();
};


#endif //MAGICBOXWM_MBAPP_H
