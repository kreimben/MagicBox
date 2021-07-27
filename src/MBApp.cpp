//
// Created by ubuntu on 7/27/21.
//

#include "MBApp.h"

#include <iostream>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

// MBApp * MBApp::_instance = 0;

MBApp::MBApp() {

    /*
     * Connect to X Server!!!
     */

    this->connect = xcb_connect(nullptr, nullptr);
    if (xcb_connection_has_error(this->connect)) { std::cout << "Error to connect X Server!" << std::endl; exit(1); }

    std::cout << "Display successfully connected!" << std::endl;

    const xcb_setup_t *setup = xcb_get_setup(this->connect);
    this->screen = xcb_setup_roots_iterator(setup).data;

    this->printScreenInfo(screen);

    /*
     * Generate Window ID
     */

    this->window_id = xcb_generate_id(this->connect);

    /*
    ** Set MASKs.
    ** */

    this->propName = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    this->props = new uint32_t[2]();
    props[0] = screen->black_pixel;
    props[1] = XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_EXPOSURE;

    /*
    ** Create Foundation Background Window.
    */

    xcb_create_window(connect,
                      XCB_COPY_FROM_PARENT,
                      this->window_id,
                      this->screen->root,
                      0, 0, 500, 300, 30,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      propName,
                      props);

    /* Display the foundation background window. */
    xcb_map_window(connect, window_id);
    xcb_flush(connect);
}

void MBApp::printScreenInfo(xcb_screen_t *screen) {

    std::cout << "screen info: " <<
    "allowed depths len: " << screen->allowed_depths_len << std::endl <<
    "backing stores: " << screen->backing_stores << std::endl <<
    "black pixel: " << screen->black_pixel << std::endl <<
    "current input masks: " << screen->current_input_masks << std::endl <<
    "default colormap: " << screen->default_colormap << std::endl <<
    "height in millimeters: " << screen->height_in_millimeters << std::endl <<
    "height in pixels: " << screen->height_in_pixels << std::endl <<
    "max installed maps: " << screen->max_installed_maps << std::endl <<
    "min installed maps: " << screen->min_installed_maps << std::endl <<
    "screen root: " << screen->root << std::endl <<
    "screen root depth: " << screen->root_depth << std::endl <<
    "screen root visual: " << screen->root_visual << std::endl << std::endl;
}

void MBApp::eventLoop() {
    std::cout << "MBApp::eventLoop()" << std::endl;

    while (auto event = xcb_wait_for_event(this->connect)) {
        std::cout << "In while loop!" << std::endl;
        switch (event->response_type) {

            case XCB_KEY_PRESS:
                std::cout << "Key pressed!: " << ((xcb_key_press_event_t *)event)->detail << std::endl;
                std::cout << "when: " << ((xcb_key_press_event_t *)event)->time << std::endl << std::endl;
                break;

            case XCB_BUTTON_PRESS:
                std::cout << "Button pressed!: " << ((xcb_button_press_event_t *)event)->detail << std::endl;
                std::cout << "when: " << ((xcb_button_press_event_t *)event)->time << std::endl << std::endl;
                break;

            default:
                std::cout << "Yet another event!: " << event->sequence << std::endl << std::endl;
                break;
        }
    }
}

void MBApp::disconnectApp() {
    xcb_disconnect(connect);
}
