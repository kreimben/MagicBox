//
// Created by ubuntu on 7/27/21.
//

#include <iostream>
#include <memory>

#include <wayland-client-core.h>

#include "MBApp.h"

MBApp::MBApp() {

    std::cout << "MBApp Initializer!" << std::endl;
    this->display = std::unique_ptr<wl_display>(wl_display_connect(nullptr));
}

std::unique_ptr<MBApp>& MBApp::getInstance() {
    if (_instance.get() == nullptr) _instance = std::make_unique<MBApp>();
    return (_instance);
}
