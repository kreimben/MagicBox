#include "MBTopBar.h"

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <memory>
#include <iostream>
#include <thread>

MBTopBar::MBTopBar(xcb_connection_t *connect, xcb_screen_t *screen, xcb_window_t rootWindowID) {

    std::cout << "MBTopBar constructor start!" << std::endl;

    this->connect = connect;
    this->screen = screen;

    /* Generate top bar's ID */
    this->topbarWindowID = xcb_generate_id(connect);
    std::cout << "top bar window id: " << this->topbarWindowID << std::endl;

    /* Get a root's width */
    auto geoInfo = xcb_get_geometry_reply(connect, xcb_get_geometry(connect, rootWindowID), nullptr);
    auto width = geoInfo->width;
    std::cout << "width: " << width << std::endl;

    /* Set masks. */
    auto value_mask = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK;
    int list[3];
    list[0] = (screen->white_pixel + screen->black_pixel) / 2;
    list[1] = screen->black_pixel;
    list[2] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_MOTION;

    /* Create MBTopBar top bar. */
    xcb_create_window(connect,
                      XCB_COPY_FROM_PARENT,
                      this->topbarWindowID,
                      rootWindowID,
                      0, 0, width, 25, 1,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      value_mask, list);

    /* Map actual things. */
    xcb_map_window(connect, this->getTopbarWindowID());
}

xcb_window_t MBTopBar::getTopbarWindowID() {
    return this->topbarWindowID;
}
