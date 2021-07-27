//
// Created by ubuntu on 7/27/21.
//

#include "MBWindow.h"
#include <xcb/xcb.h>

MBWindow::MBWindow() {

    this->window_id = xcb_generate_id();
}
