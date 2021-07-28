#include "./MBApp.h"
#include "./MBWindow.h"
#include "./MBTopBar.h"

#include <iostream>
#include <memory>

int main() {

    std::cout << "App Started!" << std::endl;

    /* Start event loop! */
    auto app = MBApp::getInstance();

    auto topBar = std::make_unique<MBTopBar>(app->getConnection(), app->getScreen(), app->getWindowID());

    /*
    ** Do Anything before execute eventLoop!!!
         */
    app->eventLoop();
    /* After quit event loop, Disconnect the window from X Server. */
    app->disconnectApp();

    std::cout << "Bye bye!" << std::endl;

    return 0;
}
