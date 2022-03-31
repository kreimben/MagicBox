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

#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-server-core.h>
#include <wlr/backend.h>
#include <wlr/render/allocator.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_output.h>

struct wl_display *display;
struct wlr_backend *backend;
struct wlr_renderer *renderer;
struct wlr_allocator *allocator;


void mb_server_ready() {

    display = wl_display_create();
    if (display == NULL) {
        printf("Can not create wl_display.");
        exit(1);
    }

    backend = wlr_backend_autocreate(display);
    if (backend == NULL) {
        printf("Can not create wlr_backend.");
        exit(1);
    }

    renderer = wlr_renderer_autocreate(backend);
    allocator = wlr_allocator_autocreate(backend, renderer);
}

void mb_server_run() {
    if (!wlr_backend_start(backend)) {
        printf("Failed to start backend.\n");
        wlr_backend_destroy(backend);
        exit(1);
    }

    printf("mb_server_run()\n");
    wl_display_run(display);
}

void mb_server_destroy_objects() {

    printf("mb_server_destroy_objects");
    wl_display_destroy(display);
}
