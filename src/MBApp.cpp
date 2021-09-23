extern "C" {
#include <string.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>
}

#include "./MBApp.h"
#include "./client/MBCompositor.h"
#include <iostream>

// wl_compositor *MBApp::compositor = nullptr;
// wl_shell *MBApp::shell = nullptr;

MBApp::MBApp() {

  // std::cout << "MBApp Initializer!" << std::endl;
  // this->display = wl_display_connect(nullptr);
  // if (this->display == nullptr) {
  //   fprintf(stderr, "Error for connection to wayland display.\n");
  //   exit(1);
  // }

  // std::cout << "Connected Successfully!" << std::endl;

  // auto registry = wl_display_get_registry(this->display);

  // const wl_registry_listener listener = {.global = registerHandler,
  //                                        .global_remove = removeHandler};

  // wl_registry_add_listener(registry, &listener, nullptr);

  // wl_display_dispatch(this->display);
  // wl_display_roundtrip(this->display);

  /* Check the compositor pointer whether NULL pointer. If null, disconnect to
   * server. */
  // if (!MBCompositor::getInstance()->isValidCompositor()) {
  //   this->disconnect();
  //   exit(1);
  // }

  this->setSurface(wl_compositor_create_surface(MBApp::compositor));
  this->setShellSurface(
      wl_shell_get_shell_surface(MBApp::shell, this->surface));

  wl_shell_surface_set_toplevel(this->shell_surface);
}

// MBApp::~MBApp() {

//   free(this->display);
//   free(_instance);
// }

MBApp *MBApp::_instance = nullptr;

MBApp *MBApp::getInstance() {
  if (_instance == nullptr)
    _instance = new MBApp();
  return _instance;
}

void MBApp::disconnect() { wl_display_disconnect(this->display); }

bool MBApp::setSurface(wl_surface *surface) {

  if (surface == nullptr) {
    std::cerr << "Can't get a surface!" << std::endl;
    return false;
  } else {
    std::cerr << "Found surface!" << std::endl;
    this->surface = surface;
    return true;
  }
}

bool MBApp::setShellSurface(wl_shell_surface *shell_surface) {

  if (shell_surface == nullptr) {
    std::cerr << "Can't find shell surface!" << std::endl;
    return false;
  } else {
    std::cerr << "Found shell surface!" << std::endl;
    this->shell_surface = shell_surface;
    return true;
  }
}
