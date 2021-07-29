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

    /* Do Anything before execute eventLoop!!! */
    std::thread([app] {
        app->eventLoop();
    }).join();

    return 0;
}
