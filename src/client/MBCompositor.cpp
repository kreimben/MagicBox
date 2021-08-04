extern "C" {
}

#include "./MBCompositor.h"

MBCompositor::MBCompositor() {

    this->_compositor = nullptr;
}

bool MBCompositor::isValidCompositor() {

  if (this->_compositor == nullptr) {
    std::cerr << "Can't find compositor!" << std::endl;
    return false;
  } else {
    std::cerr << "Found compositor!" << std::endl;
    return true;
  }
}
