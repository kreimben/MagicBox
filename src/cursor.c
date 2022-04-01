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
 * system
 */
#include <stdlib.h>

/*
 * wlroots
 */
#include <wlr/types/wlr_input_device.h>
#include <wlr/xcursor.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_xcursor_manager.h>

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

static void seat_request_cursor(struct wl_listener *listener, void *data) {
    struct magicbox_server *server = wl_container_of(listener, server, request_cursor);
    // This event is raised by the seat when a client provides a cursor image.
    struct wlr_seat_pointer_request_set_cursor_event *event = data;
    struct wlr_seat_client *focused_client = server->seat->pointer_state.focused_client;

    // This can be sent by any client, so we check to make sure this one is actually has pointer focus first.
    if (focused_client == event->seat_client) {
        // Once we've vetted the client, we can tell the cursor to use the provided surface as the cursor image.
        // It will set the hardware cursor on the output that it's currently on and continue to do so as the cursor moves between outputs.
        wlr_cursor_set_surface(server->cursor,
                               event->surface,
                               event->hotspot_x,
                               event->hotspot_y);
    }
}

static void seat_request_set_selection(struct wl_listener *listener, void *data) {
    struct magicbox_server *server = wl_container_of(listener, server, request_set_selection);

    // This event is raised by the seat when a client provides a cursor image
    struct wlr_seat_request_set_selection_event *event = data;
    wlr_seat_set_selection(server->seat, event->source, event->serial);
}

static void process_cursor_move(struct magicbox_server *server, uint32_t time) {
    // Move grabbed view to the new position.
    struct magicbox_view *view = server->grabbed_view;
    view->x = server->cursor->x - server->grab_x;
    view->y = server->cursor->y - server->grab_y;
    wlr_scene_node_set_position(view->scene_node, view->x, view->y);
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
    wlr_xdg_surface_get_geometry(view->xdg_toplevel->base, &geo_box);
    view->x = new_left - geo_box.x;
    view->y = new_top - geo_box.y;
    wlr_scene_node_set_position(view->scene_node, view->x, view->y);

    int new_width = new_right - new_left;
    int new_height = new_bottom - new_top;
    wlr_xdg_toplevel_set_size(view->xdg_toplevel, new_width, new_height);
}

static void process_cursor_motion(struct magicbox_server *server, uint32_t time) {
    // If mode is non-passthrough, Delegate to those functions.
    if (server->cursor_mode == MB_CURSOR_MOVE) {
        process_cursor_move(server, time);
        return;
    } else if (server->cursor_mode == MB_CURSOR_RESIZE) {
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
        wlr_xcursor_manager_set_cursor_image(server->cursor_manager,
                                             "left_ptr",
                                             server->cursor);
    }

    if (surface) {
        /*
         * Send pointer enter and motion events.
         *
         * The enter event gives the surface "pointer focus", which is distinct from keyboard focus.
         * You get pointer focus by moving the pointer over a window.
         *
         * Note that wlroots will avoid sending duplicate enter/motion events if the surface has already
         * or has pointer focus or if the client is already aware of the coordinates passed.
         */
        wlr_seat_pointer_enter(seat, surface, sx, sy);
        wlr_seat_pointer_notify_motion(seat, time, sx, sy);
    } else {
        /*
         * Clear pointer focus so future button events and such are not sent to the last client
         * to have the cursor over it.
         */
        wlr_seat_pointer_clear_focus(seat);
    }
}

static void server_cursor_motion(struct wl_listener *listener, void *data) {
    /*
     * This event is forwarded by the cursor when a pointer emits a _relative_
     * pointer motion event (i.e. a delta)
     */
    struct magicbox_server *server = wl_container_of(listener, server, cursor_motion);
    struct wlr_pointer_motion_event *event = data;

    /*
     * The cursor doesn't move unless we tell it to.
     * The cursor automatically handles constraining the motion to the output layout,
     * as well as any special configuration applied for the specific input device
     * which generated the event.
     * You can pass NULL for the device if you want to move the cursor around without any input.
     */
    wlr_cursor_move(server->cursor, &event->pointer->base,
                    event->delta_x, event->delta_y);
    process_cursor_motion(server, event->time_msec);
}

static void server_cursor_motion_absolute(struct wl_listener *listener, void *data) {
    /*
     * This event is forwarded by the cursor when a pointer emits an _absolute_ motion event,
     * from 0..1 on each axis. this happens, for example, when wlroots is running under a Wayland window
     * rather than KMS+DRM, and you move the mouse over the window.
     * You could enter the window from any edge, so we have to warp the mouse there.
     * There is also some hardware which emits these events.
     */
    struct magicbox_server *server = wl_container_of(listener, server, cursor_motion_absolute);
    struct wlr_pointer_motion_absolute_event *event = data;
    wlr_cursor_warp_absolute(server->cursor, &event->pointer->base,
                             event->x, event->y);
    process_cursor_motion(server, event->time_msec);
}

static void server_cursor_button(struct wl_listener *listener, void *data) {
    /*
     * This event is forwarded by the cursor when a pointer emits a button event.
     */
    struct magicbox_server *server = wl_container_of(listener, server, cursor_button);
    struct wlr_pointer_button_event *event = data;

    /*
     * Notify the client with pointer focus that a button press has occurred.
     */
    wlr_seat_pointer_notify_button(server->seat,
                                   event->time_msec,
                                   event->button,
                                   event->state);
    double sx, sy;
    struct wlr_surface *surface = NULL;
    struct magicbox_view *view = desktop_view_at(server,
                                                 server->cursor->x, server->cursor->y,
                                                 &surface,
                                                 &sx, &sy);

    if (event->state == WLR_BUTTON_RELEASED) {
        // If you released any buttons, we exit interactive move/resize mode.
        server->cursor_mode = MB_CURSOR_PASSTHROGH;
    } else {
        // Focus that client if the button was _pressed_.
        focus_view(view, surface);
    }
}

static void server_cursor_axis(struct wl_listener *listener, void *data) {
    /*
     * This event is forwarded by the cursor when a pointer emits an axis event,
     * for example when you move the scroll wheel.
     */
    struct magicbox_server *server = wl_container_of(listener, server, cursor_axis);
    struct wlr_pointer_axis_event *event = data;
    /* Notify the client with pointer focus of the axis event. */
    wlr_seat_pointer_notify_axis(server->seat,
                                 event->time_msec,
                                 event->orientation,
                                 event->delta,
                                 event->delta_discrete,
                                 event->source);
}

static void server_cursor_frame(struct wl_listener *listener, void *data) {
    /*
     * This event is forwarded by the cursor when a pointer emits a frame event.
     * Frame events are sent after regular pointer events to group multiple events together.
     * For instance, two axis events may happen at the same item, in which case a frame event won't be sent in between.
     */
    struct magicbox_server *server = wl_container_of(listener, server, cursor_frame);
    /* Notify the client with pointer focus of the frame event. */
    wlr_seat_pointer_notify_frame(server->seat);
}

static void output_frame(struct wl_listener *listener, void *data) {
    /*
     * This function is called every time an output is ready to display a frame,
     * generally at the output's refresh rate (e.g. 60Hz).
     */
    struct magicbox_output *output = wl_container_of(listener, output, frame);
    struct wlr_scene *scene = output->server->scene;
    struct wlr_scene_output *scene_output = wlr_scene_get_scene_output(scene, output);

    /* Render the scene if needed and commit the output. */
    wlr_scene_output_commit(scene_output);

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    wlr_scene_output_send_frame_done(scene_output, &now);
}

static void server_new_output(struct wl_listener *listener, void *data) {
    /* This event is raised by the backend when a new output (aka a display or monitor) becomes available. */
    struct magicbox_server *server = wl_container_of(listener, server, new_output);
    struct wlr_output *wlr_output = data;

    /* Configures the output created by the backend to use our allocator and our renderer.
     * Must be done once, before commiting the output. */
    wlr_output_init_render(wlr_output, server->allocator, server->renderer);

    /*
     * Some backends don't have modes. DRM+KMS does, and we need to set a mode before we can use the output.
     * The mode is a tuple of (width, height, refresh rate), and each monitor supports only a specific set of modes.
     * We just pick the monitor's preferred mode, a more sophisticated compositor would let the user configure it.
     */
    if (!wl_list_empty(&wlr_output->modes)) {
        struct wlr_output_mode *mode = wlr_output_preferred_mode(wlr_output);
        wlr_output_set_mode(wlr_output, mode);
        wlr_output_enable(wlr_output, true);
        if (!wlr_output_commit(wlr_output)) {
            return;
        }
    }

    /* Allocates and configures out state for this output */
    struct magicbox_output *output = calloc(1, sizeof(struct magicbox_output));
    output->wlr_output = wlr_output;
    output->server = server;

    /* Sets up a listener for the frame notify event. */
    output->frame.notify = output_frame;
    wl_signal_add(&wlr_output->events.frame, &output->frame);
    wl_list_insert(&server->outputs, &output->link);

    /*
     * Adds this to the output layout.
     * The add_auto function arranges outputs from left-to-right in the order they appear.
     * A more sophisticated compositor would let the user configure the arrangement of outputs in the layout.
     *
     * The output layout utility automatically adds a wl_output global to the display,
     * which Wayland clients can see to find out information about the output
     * (such as DPI, scale factor, manufacturer, etc).
     */
    wlr_output_layout_add_auto(server->output_layout, wlr_output);
}