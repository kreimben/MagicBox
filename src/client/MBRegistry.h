extern "C" {
#include <wayland-client.h>
}

#include <functional>
#include <iostream>
#include <wayland-client-protocol.h>

class MBRegistry {

private:
  MBRegistry(wl_registry *reg);
  static MBRegistry *_instance;
  /* Get registry object from wl_display_get_registry(); function */
  wl_registry *_registry;
  wl_registry_listener _listener;

public:
  static MBRegistry *getInstance();
  /* Get registry object from wl_display_get_registry(); function */
  inline void setRegistry(wl_registry *registry) { this->_registry = registry; }
  void bind(uint32_t name, const struct wl_interface *interface,
            std::function<void(void *)> completion);
};
