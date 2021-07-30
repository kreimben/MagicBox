//
// Created by ubuntu on 7/27/21.
//

#include <iostream>
#include <memory>

#include "MBApp.h"

MBApp::MBApp() { }

MBApp * MBApp::_instance = nullptr;

MBApp* MBApp::getInstance() {
    if (_instance == nullptr) _instance = new MBApp();
    return _instance;
}
