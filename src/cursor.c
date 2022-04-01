/*
 * Copyright 2022 Aksidion Kreimben
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * MagicBox
 */
#include "cursor.h"
#include "server.h"
#include "keyboard.h"
#include "view.h"

/*
 * wlroots
 */
#include <wlr/types/wlr_input_device.h>
#include <wlr/xcursor.h>

static void server_new_pointer(struct magicbox_server *server, struct wlr_input_device *device) {
    // Handle pointers.
    wlr_cursor_attach_input_device(server->cursor, device);
}

void server_new_input(struct wl_listener *listener, void *data) {
    // This event is raised by the backend when a new input device becomes available.
    struct magicbox_server *server = wl_container_of(listener, server, new_input);
    struct wlr_input_device *device = data;
    switch (device->type) {
        case WLR_INPUT_DEVICE_KEYBOARD:
            server_new_keyboard(server, device);
            break;
        case WLR_INPUT_DEVICE_POINTER:
            server_new_pointer(server, device);
            break;
        default:
            break;
    }

    // We need to let the wlr_seat know what out capabilities are, which is communicated to the client.
    uint32_t caps = 0;
    if (!wl_list_empty(&server->keyboards)) caps |= WL_SEAT_CAPABILITY_KEYBOARD;
    if (!server->cursor) caps |= WL_SEAT_CAPABILITY_POINTER;
    wlr_seat_set_capabilities(server->seat, caps);
}

static void seat_request_set_selection(struct wl_listener *listener, void *data) {
    struct magicbox_server *server = wl_container_of(listener, server, request_cursor);

    // This event is raised by the seat when a client provides a cursor image
    struct wlr_seat_pointer_request_set_cursor_event *event = data;
    struct wlr_seat_client *focused_client = server->seat->pointer_state.focused_client;

    // Thia can be sent by any client, so we check to make sure this one is actually has pointer focus first.
    if (focused_client == event->seat_client) {
        wlr_cursor_set_surface(server->cursor,
                               event->surface,
                               event->hotspot_x,
                               event->hotspot_y);
    }
}

static void process_cursor_move(struct magicbox_server *server, uint32_t time) {
    // Move grabbed view to the new position.
    server->grabbed_view->x = server->cursor->x - server->grab_x;
    server->grabbed_view->y = server->cursor->y - server->grab_y;
}

static void process_cursor_resize(struct magicbox_server *server, uint32_t time) {
    // Resizing grabbed view can be a little bit complicated, because we could be resizing from any corner or edge.
    // This now only resizes the view on one or two axes, but can also move the view if you resize from the top or left edges (or top-left corner).
    //
    // Note that I took some shortcuts here. In a more fleshed-out compositor,
    // You'd wait for the client to prepare a buffer at the new size, then commit any movement that was prepared.
    struct magicbox_view *view = server->grabbed_view;
    double border_x = server->cursor->x - server->grab_x;
    double border_y = server->cursor->y - server->grab_y;
    int new_left = server->grab_geobox.x;
    int new_right = server->grab_geobox.x + server->grab_geobox.width;
    int new_top = server->grab_geobox.y;
    int new_bottom = server->grab_geobox.y + server->grab_geobox.height;

    if (server->resize_edges & WLR_EDGE_TOP) {
        new_top = border_y;
        if (new_top >= new_bottom) {
            new_top = new_bottom - 1;
        }
    } else if (server->resize_edges & WLR_EDGE_BOTTOM) {
        new_bottom = border_y;
        if (new_bottom <= new_top) {
            new_bottom = new_top + 1;
        }
    }

    if (server->resize_edges & WLR_EDGE_LEFT) {
        new_left = border_x;
        if (new_left >= new_right) {
            new_left = new_right - 1;
        }
    } else if (server->resize_edges & WLR_EDGE_RIGHT) {
        new_right = border_x;
        if (new_right <= new_left) {
            new_right = new_left + 1;
        }
    }

    struct wlr_box geo_box;
    wlr_xdg_surface_get_geometry(view->xdg_surface, &geo_box);
    view->x = new_left - geo_box.x;
    view->y = new_top - geo_box.y;

    int new_width = new_right - new_left;
    int new_height = new_bottom - new_top;
    wlr_xdg_toplevel_set_size(view->xdg_surface, new_width, new_height);
}

static void process_cursor_motion(struct magicbox_server *server, uint32_t time) {
    // If mode is non-passthrough, Delegate to those functions.
    if (server->cursur_mode == MB_CURSOR_MOVE) {
        process_cursor_move(server, time);
        return;
    } else if (server->cursur_mode == MB_CURSOR_RESIZE) {
        process_cursor_resize(server, time);
    }

    // Otherwise, Find the view under the pointer and send the event along.
    double sx, sy;
    struct wlr_seat *seat = server->seat;
    struct wlr_surface *surface = NULL;
    struct magicbox_view *view = desktop_view_at(server,
                                                 server->cursor->x, server->cursor->y,
                                                 &surface, &sx, &sy);

    if (!view) {
        /*
         * If there's no view under the cursor, set the cursor image to a default.
         * This is what makes the cursor image appear when you move it around the screen, not over any views.
         */
        wlr_xcursor_manager_set_cursor_image(server->cursor_manager, "left_ptr", server->cursor);
    }
}