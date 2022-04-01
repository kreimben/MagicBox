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
#include "view.h"
#include "server.h"

/*
 * wayland
 */
#include <wayland-server-core.h>

/*
 * wlroots
 */
#include <wlr/types/wlr_surface.h>
#include <wlr/types/wlr_seat.h>

static void focus_view(struct magicbox_view *view, struct wlr_surface *surface) {
    // keyboard focus.
    if (!view) return;

    // Ready for convenient
    struct magicbox_server *server = view->server;
    struct wlr_seat *seat = server->seat;
    struct wlr_surface *prev_surface = seat->keyboard_state.focused_surface;

    if (prev_surface == surface) return; // Don't need to re-focus.

    if (prev_surface) {
        // Deactive previous focused surface.
        struct wlr_xdg_surface *previous = wlr_xdg_surface_from_wlr_surface(
                seat->keyboard_state.focused_surface
        );
        wlr_xdg_toplevel_set_activated(previous, false);
    }

    struct wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat);

    // Move the view to the front.
    wl_list_remove(&view.link);
    wl_list_insert(&server->views, &view->link);

    // Activate the new surface.
    wlr_xdg_toplevel_set_activated(view->xdg_surface, true);

    /*
	 * Tell the seat to have the keyboard enter this surface. wlroots will keep
	 * track of this and automatically send key events to the appropriate
	 * clients without additional work on your part.
	 */
    wlr_seat_keyboard_notify_enter(seat,
                                   view->xdg_surface->surface,
                                   keyboard->keycodes,
                                   keyboard->num_keycodes,
                                   &keyboard->modifiers);
}

static bool view_at(struct magicbox_view *view,
                    double lx, double ly,
                    struct wlr_surface **surface,
                    double *sx, double *sy) {

    // XDG toplevels may have nested surfaces, such as popup windows for context menus or tooltips.
    // This function tests if any of those are underneath the coordinates lx and ly (in output Layout Coordinates).
    // If so, it sets the surface pointer to that wlr_surface and the sx and sy coordinates
    // to the coordinates relative to that surface's top-left corner.
    double view_sx = lx - view->x;
    double view_sy = ly - view->y;

    double _sx, _sy;
    struct wlr_struct *_surface = NULL;
    _surface = wlr_xdg_surface_surface_at(view->xdg_surface,
                                          view_sx, view_sy,
                                          &_sx, &_sy);

    if (_surface == NULL) {
        *sx = _sx;
        *sy = _sy;
        *surface = _surface;
        return true;
    }

    return false;
}

struct magicbox_view *desktop_view_at(
        struct magicbox_server *server, double lx, double ly,
        struct wlr_surface **surface, double *sx, double *sy) {

    // This iterates over all of our surfaces and attempts to find one under the cursor.
    // This relies on server->views being ordered from top-to-bottom.
    struct magicbox_view *view;
    wl_list_for_each(view, &server->views, link) {
        if (view_at(view, lx, ly, surface, sx, sy)) {
            return view;
        }
    }
    return NULL;
}