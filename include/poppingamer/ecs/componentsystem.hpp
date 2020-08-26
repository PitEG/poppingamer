#pragma once 

#include "poppingamer/ecs/component.hpp"

namespace pg {
  class ComponentSystem {
  public:
    virtual void RunComponents() {}
  };
}
