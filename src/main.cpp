#include <iostream>
#include <memory>

extern "C" {
#include <wayland-client-core.h>
#include <wayland-util.h>
#include <wayland-version.h>
}

#include "MBApp.h"

int main() {

  std::cout << "Welcome to MagicBox!" << std::endl;

  auto instance = MBApp::getInstance();

  // instance->disconnect();

  return 0;
}
