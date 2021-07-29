#include "./MBApp.h"
#include "./MBWindow.h"
#include "./MBTopBar.h"

#include <iostream>
#include <memory>
#include <thread>

int main() {

    std::cout << "Welcome to MagicBoxWM!" << std::endl;

    /* Start event loop! */
    auto app = MBApp::getInstance();

    // auto topBar = std::make_unique<MBTopBar>(app->getConnection(), app->getScreen(), app->getWindowID());

    /* Do Anything before execute eventLoop!!! */
    std::thread([app] {
        app->eventLoop();
    }).join();
    /* After quit event loop, Disconnect the windostd::shared_ptr<w from X Ser> r. */
    // app->disconnectApp();
    std::cout << "Bye bye!" << std::endl;

    return 0;
}
