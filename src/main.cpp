#include "./MBApp.h"

#include <iostream>
#include <memory>

int main() {

    std::cout << "App Started!" << std::endl;

    /* Start event loop! */
    auto app = std::make_unique<MBApp>();
    app->eventLoop();

    /* After quit event loop, Disconnect the window from X Server. */
    app->disconnectApp();

    std::cout << "Bye bye!" << std::endl;

    return 0;
}
