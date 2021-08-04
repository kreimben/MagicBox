#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
extern "C" {
#include <cstdio>
#include <wayland-client.h>
}

#include <iostream>

#include "./MBDisplay.h"

MBDisplay::MBDisplay() {

  /* Initializing wl_display object in this class! */
  this->_display = wl_display_connect(nullptr);

  /* Check null pointer. */
  if (this->_display == nullptr) {
    fprintf(stderr, "Error for connection to wayland display.\n");
    exit(1);
  }

  std::cout << "Connected Successfully!" << std::endl;
}

void MBDisplay::dispatch() {
    wl_display_dispatch(this->_display);
}

void MBDisplay::roundtrip() {
    wl_display_roundtrip(this->_display);
}

wl_registry *MBDisplay::generateRegistry() {
    return wl_display_get_registry(this->_display);
}
