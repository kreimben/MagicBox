#include "MBTopBar.h"

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <memory>
#include <iostream>

MBTopBar::MBTopBar(std::shared_ptr<xcb_connection_t> connect, std::shared_ptr<xcb_screen_t> screen, xcb_window_t rootWindowID) {

    this->connect = connect;

    /* Generate top bar's ID */
    this->topbarWindowID = xcb_generate_id(connect.get());

    /* Get a root's width */
    auto geoInfo = xcb_get_geometry_reply(connect.get(), xcb_get_geometry(connect.get(), rootWindowID), nullptr);
    auto width = geoInfo->width;

    /* Set masks. */
    auto value_mask = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK;
    int list[3];
    list[0] = (screen->white_pixel + screen->black_pixel) / 2;
    list[1] = screen->black_pixel;
    list[2] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_MOTION;

    /* Create MBTopBar top bar. */
    xcb_create_window(connect.get(),
                      XCB_COPY_FROM_PARENT,
                      this->topbarWindowID,
                      rootWindowID,
                      0, 0, width, 50, 1,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      value_mask, list);

    /* Map actual things. */
    xcb_map_window(connect.get(), this->getTopbarWindowID());

    this->eventLoop();
}

void MBTopBar::eventLoop() {
    xcb_generic_event_t *event;

    while (event = xcb_poll_for_event(this->connect.get())) {
        switch (event->response_type) {
            case XCB_BUTTON_PRESS: {
                xcb_button_press_event_t *event = event;

                std::cout << "button pressed!" << std::endl;
                std::cout << "event x: " << event->event_x << std::endl;
                std::cout << "event y: " << event->event_y << std::endl;
                std::cout << "when: " << event->time << std::endl;
            }
        }
    }
}
