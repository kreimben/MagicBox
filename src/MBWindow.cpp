//
// Created by ubuntu on 7/27/21.
//

#include "MBWindow.h"
#include "MBApp.h"
#include <xcb/xcb.h>
#include <xcb/xproto.h>

MBWindow::MBWindow() {

    auto instance = MBApp::getInstance();
    this->window_id = xcb_generate_id(instance->getConnection());

    auto parm = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK;
    int params[3];
    auto screen = instance->getScreen();
    params[0] = screen->white_pixel;
    params[1] = screen->black_pixel;
    params[2] = XCB_EVENT_MASK_FOCUS_CHANGE;

    xcb_create_window(instance->getConnection(),
                      XCB_COPY_FROM_PARENT,
                      this->window_id,
                      instance->getWindowID(),
                      10, 10, 50, 50, 10,
                      XCB_WINDOW_CLASS_COPY_FROM_PARENT,
                      screen->root_visual,
                      parm, params);

    xcb_map_subwindows(instance->getConnection(), this->window_id);
    xcb_flush(instance->getConnection());
}

void MBWindow::eventLoop() {
    auto root_instance = MBApp::getInstance();

    while (xcb_generic_event_t *event = xcb_wait_for_event(root_instance->getConnection())) {
        switch (event->response_type) {
            default: std::cout << "some event happened!: " << event->full_sequence << std::endl;
        }
    }
}
