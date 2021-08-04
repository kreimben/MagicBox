extern "C" {
#include <wayland-client-protocol.h>
#include <wayland-client.h>
}

#include <iostream>

class MBCompositor {

private:
  MBCompositor();
  static MBCompositor *_instance;
  wl_compositor *_compositor;
  bool isValidCompositor();

public:
  static MBCompositor *getInstance();
  inline void setCompositor(wl_compositor *compositor) {
    this->_compositor = compositor;
    if (!this->isValidCompositor()) {
        /* TODO: disconnect */
        exit(1);
    }
  }
};
