#pragma once  

#include <vector>
#include <string>

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  class Entity;

  class Scene {
  public:
    Scene();
    ~Scene();

    inline const std::string& Name() const { return m_name; }
    inline const std::vector<Entity*>& GetEntities() const { return m_entities; }

  private:
    std::string m_name;
    std::vector<Entity*> m_entities;
  };
}
