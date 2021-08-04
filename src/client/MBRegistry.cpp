extern "C" {
#include <cstring>
#include <wayland-client-protocol.h>
#include <wayland-client.h>
}

#include <iostream>

#include "./MBCompositor.h"
#include "./MBRegistry.h"

void registerHandler(void *data, struct wl_registry *registry, uint32_t id,
                     const char *interface, uint32_t version) {

  std::cout << std::endl
            << "Got a event from registry!" << std::endl
            << "interface: " << interface << std::endl
            << "id: " << id << std::endl
            << "version: " << version << std::endl
            << std::endl;

  if (strcmp(interface, "wl_compositor") == 0) {
    // MBApp::compositor = (wl_compositor *)wl_registry_bind(registry, id,
    // &wl_compositor_interface, 1);
    MBRegistry::getInstance()->bind(
        id, &wl_compositor_interface, [](void *result) {
          MBCompositor::getInstance()->setCompositor((wl_compositor *)result);
        });
  } else if (strcmp(interface, "wl_shell") == 0) {
    // MBApp::shell = (wl_shell *)wl_registry_bind(registry, id,
    // &wl_shell_interface, 1);
  }
}

void removeHandler(void *data, struct wl_registry *registry, uint32_t name) {
  std::cout << "remove from handler: " << name << std::endl;
}

MBRegistry::MBRegistry(wl_registry *registry) : _registry(registry) {

  this->_listener = {.global = registerHandler, .global_remove = removeHandler};

  wl_registry_add_listener(this->_registry, &this->_listener, nullptr);
}

void MBRegistry::bind(uint32_t name, const struct wl_interface *interface,
                      std::function<void(void *)> completion) {

  auto result = wl_registry_bind(this->_registry, name, interface, 1);

  completion(result);
}
