#include <iostream>
#include <memory>

#include <wayland-client-core.h>
#include <wayland-util.h>
#include <wayland-version.h>

#include "MBApp.h"

int main() {

    std::cout << "Welcome to MagicBox!" << std::endl;

    MBApp::getInstance();

    return 0;
}
