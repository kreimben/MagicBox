//
// Created by ubuntu on 7/27/21.
//

#include <iostream>

#include <wayland-client-core.h>

#include "MBApp.h"

MBApp::MBApp() {

    std::cout << "MBApp Initializer!" << std::endl;
    this->display = wl_display_connect(nullptr);
}

MBApp::~MBApp() {

    free(this->display);
    free(_instance);
}

MBApp *MBApp::_instance = nullptr;

MBApp* MBApp::getInstance() {
    if (_instance == nullptr) _instance = new MBApp();
    return _instance;
}
