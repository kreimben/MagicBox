#include "./MBApp.h"
#include "./MBWindow.h"

#include <iostream>
#include <memory>

int main() {

    std::cout << "App Started!" << std::endl;

    /* Start event loop! */
    auto app = MBApp::getInstance();

    //auto window = std::make_unique<MBWindow>(app->getConnection(), app->getScreen(), app->getWindowID());
    //std::cout << "subwindow's id: " << window->window_id << std::endl;

    /*
    ** Do Anything before execute eventLoop!!!
         */
    app->eventLoop();
    /* After quit event loop, Disconnect the window from X Server. */
    app->disconnectApp();

    std::cout << "Bye bye!" << std::endl;

    return 0;
}
