#pragma once 

#include <vector>
#include <unordered_map>

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  template<typename T>
  class ComponentManager {
  private:
    std::vector<T>                            m_components;

  public:
    void Create(Entity& e);

  private:
  };
}
