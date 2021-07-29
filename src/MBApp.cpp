//
// Created by ubuntu on 7/27/21.
//

#include <iostream>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <memory>

#include "MBApp.h"
#include "MBTopBar.h"

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

    std::cout << "genrate window id: ";
    this->window_id = xcb_generate_id(this->connect);
    std::cout << this->window_id << std::endl;

    /*
    ** Set MASKs.
    ** */

    this->propName = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_EVENT_MASK;
    this->props = new uint32_t[3]();
    props[0] = screen->white_pixel;
    props[1] = screen->black_pixel;
    props[2] = XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_EXPOSURE;

    /*
    ** Create Foundation Background Window.
    */

    std::cout << "Before create window!" << std::endl;
    xcb_create_window(connect,
                      this->screen->root_depth,
                      this->window_id,
                      this->screen->root,
                      0, 0, 1024, 768, 30,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual,
                      propName,
                      props);

    /* Display the foundation background window. */
    std::cout << "Before map window" << std::endl;
    xcb_map_window(connect, window_id);
    std::cout << "Before flush" << std::endl;
    xcb_flush(connect);
}

void MBApp::printScreenInfo(xcb_screen_t *screen) {

    std::cout << "screen info: " <<
    "allowed depths len: " << screen->allowed_depths_len << std::endl <<
    "backing stores: " << screen->backing_stores << std::endl <<
    "black pixel: " << screen->black_pixel << std::endl <<
    "white pixel: " << screen->white_pixel << std::endl <<
    "current input masks: " << screen->current_input_masks << std::endl <<
    "default colormap: " << screen->default_colormap << std::endl <<
    "width in millimeters: " << screen->width_in_millimeters << std::endl <<
    "width in pixels: " << screen->width_in_pixels << std::endl <<
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

    /* Call child windows here so check the window_id */
    MBTopBar topbar(this->getConnection(), this->getScreen(), this->getWindowID());

    while (auto event = xcb_wait_for_event(this->connect)) {

        xcb_flush(this->connect);

        std::cout << "In while loop!" << std::endl;
        switch (event->response_type) {

            case XCB_KEY_PRESS:
                std::cout << "Key pressed!: " << ((xcb_key_press_event_t *)event)->detail << std::endl;
                std::cout << "when: " << ((xcb_key_press_event_t *)event)->time << std::endl << std::endl;
                break;

            case XCB_BUTTON_PRESS: {

                auto ev = (xcb_button_press_event_t *)event;

                if (ev->event == this->getWindowID()) { // Background

                    std::cout << "Button pressed!: " << ev->detail << std::endl;
                    std::cout << "event x: " << ev->event_x << std::endl;
                    std::cout << "event y: " << ev->event_y << std::endl;
                    std::cout << "when: " << ev->time << std::endl << std::endl;

                } else if (ev->event == topbar.getTopbarWindowID()) {

                    std::cout << "Top Bar clicked!" << std::endl;
                }

                delete ev;
                break;
            }

            case XCB_MOTION_NOTIFY: {
                auto mot = (xcb_motion_notify_event_t *)event;
                if (mot->event != this->getWindowID()) {
                    std::cout << "you are dragging mouse!" << std::endl;
                    std::cout << "x: " << mot->event_x << " y: " << mot->event_y << std::endl;

                    int16_t conf[2] = { mot->event_x, mot->event_y };

                    xcb_configure_window(this->connect,
                                         mot->event,
                                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,
                                         conf);
                    xcb_flush(this->connect);
                }
                break;
            }

            default:
                std::cout << "Yet another event!: " << event->sequence << std::endl << std::endl;
                break;
        }
    }
}

void MBApp::disconnectApp() {
    xcb_disconnect(connect);
}

MBApp * MBApp::_instance = nullptr;

MBApp* MBApp::getInstance() {
    if (_instance == nullptr) _instance = new MBApp();
    return _instance;
}

xcb_connection_t *MBApp::getConnection() {
    return this->connect;
}

xcb_window_t MBApp::getWindowID() {
    return this->window_id;
}

xcb_screen_t *MBApp::getScreen() {
    return this->screen;
}
