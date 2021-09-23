#pragma once

extern "C" {
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
}

#include <iostream>
#include <memory>

class MBApp {

private:
  MBApp();
  ~MBApp();
  static MBApp *_instance;

  wl_display *display;
  wl_surface *surface;
  wl_shell_surface *shell_surface;

  bool checkCompositor(wl_compositor *compositor);
  bool setSurface(wl_surface *surface);
  bool setShellSurface(wl_shell_surface *shell_surface);

public:
  static MBApp *getInstance();

  /* Global Objects of Wayland client. */
  // static wl_compositor *compositor;
  static wl_shell *shell;

  void disconnect();
};
