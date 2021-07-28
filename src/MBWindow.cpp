//
// Created by ubuntu on 7/27/21.
//

#include "MBWindow.h"
#include "MBApp.h"
#include <xcb/xcb.h>
#include <xcb/xproto.h>

MBWindow::MBWindow(xcb_connection_t *connect, xcb_screen_t *screen, xcb_window_t rootWindowID) {

    std::cout << "MBWindow Instanciated!" << std::endl;

    //auto instance = MBApp::getInstance();
    this->window_id = xcb_generate_id(connect);

    auto parm = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK;
    int params[3];
    params[0] = (screen->white_pixel + screen->black_pixel) / 2;
    params[1] = screen->black_pixel;
    params[2] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_MOTION;

    xcb_create_window(connect,
                      XCB_COPY_FROM_PARENT,
                      this->window_id,
                      rootWindowID,
                      10, 10, 50, 50, 10,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      parm, params);

    xcb_map_window(connect, this->window_id);
    xcb_flush(connect);
}
