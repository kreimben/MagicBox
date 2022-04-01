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
#include "keyboard.h"

/*
 * system
 */
#include <stdlib.h>

/*
 * wayland
 */
#include <wayland-server-core.h>

/*
 * wlroots
 */
#include <wlr/types/wlr_surface.h>
#include <wlr/types/wlr_seat.h>

/*
 * XKB
 */
#include <xkbcommon/xkbcommon-keysyms.h>

static void keyboard_handle_modifiers(struct wl_listener *listener, void *data) {
    // When user hit modifier keys. e.g. Alt, Shift, Ctrl...
    struct magicbox_keyboard *keyboard = wl_container_of(listener, keyboard, modifiers);

    // Set all keyboards to wayland.
    wlr_seat_set_keyboard(keyboard->server->seat, keyboard->device);

    // send modifiers to the client
    wlr_seat_keyboard_notify_modifiers(keyboard->server->seat,
                                       &keyboard->device->keyboard->modifiers);
}

static bool handle_keybinding(struct magicbox_server *server, xkb_keysym_t sym) {
    // Handle compositor keybindings.
    switch (sym) {
        case XKB_KEY_Escape:
            wl_display_terminate(server->wl_display);
            break;
        case XKB_KEY_F1:
            // Cycle to the next view
            if (wl_list_length(&server->views) < 2) break;
            struct magicbox_view *current_view = wl_container_of(
            server->views.next, current_view, link)
            );
            struct magicbox_view *next_view = wl_container_of(
                    server->link.next, next_view, link
            );
            focus_view(next_view, next_view->xdg_surface->surface);
            // Move the previous view to the end of the list
            wl_list_remove(&current_view->link);
            wl_list_insert(server->views.prev, &current_view->link);
            break;
        default:
            return false;
    }
    return true;
}

static void keybaord_handle_key(struct wl_listener *listener, void *data) {
    struct magicbox_keyboard *keyboard = wl_container_of(listener, keyboard, key);
    struct magicbox_server *server = keyboard->server;
    struct wlr_event_keyboard_key *event = data;
    struct wlr_seat *seat = server->seat;

    // Translate libinput keycode -> xkbcommon
    uint32_t keycode = event->keycode + 8;

    // Get a list of keysyms based on the keymap for this keyboard.
    const xkb_keysym_t *syms;
    int nsyms = xkb_state_key_get_syms(keyboard->device->keyboard->xkb_state,
                                       keycode,
                                       &syms);

    bool handled = false;
    uint32_t modifiers = wlr_keyboard_get_modifiers(keyboard);
    if ((modifiers & WLR_MODIFIER_LOGO) && event->state == WL_KEYBOARD_KEY_STATE_PRESSED) {
        for (int i = 0; i < nsyms; i++)
            handled = handle_keybinding(server, syms[i]);
    }

    if (!handled) {
        // Otherwise, we pass it along to the client
        wlr_seat_set_keyboard(seat, keyboard->device);
        wlr_seat_keyboard_notify_key(seat,
                                     event->time_msec,
                                     event->keycode,
                                     event->state);
    }
}

void server_new_keyboard(struct magicbox_server *server, struct wlr_input_device *device) {
    struct magicbox_keyboard *keyboard = calloc(1, sizeof(struct magicbox_keyboard));
    keyboard->server = server;
    keyboard->device = device;

    // Prepare XKB keymap and assign it to the keybaord.
    struct xkb_context *context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    struct xkb_keymap *keymap = xkb_keymap_new_from_names(context,
                                                          NULL,
                                                          XKB_KEYMAP_COMPILE_NO_FLAGS);

    wlr_keyboard_set_keymap(device->keyboard, keymap);
    xkb_keymap_unref(keymap);
    xkb_context_unref(context);
    wlr_keyboard_set_repeat_info(device->keyboard, 25, 600);

    // Set listener for keyboard events.
    keyboard->modifiers.notify = keyboard_handle_modifiers;
    wl_signal_add(&device->keyboard->events.modifiers, &keyboard->modifiers);
    keyboard->key.notify = keybaord_handle_key;
    wl_signal_add(&device->keyboard->events.key, &keyboard->key);

    wlr_seat_set_keyboard(server->seat, device);

    // And add the keyboard to out list of keyboards.
    wl_list_insert(&server->keyboards, &keyboard->link);
}