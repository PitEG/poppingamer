#pragma once 

#include <vector>
#include <string>

#include "poppingamer/ecs/entity.hpp"
#include "poppingamer/ecs/objectpooler.hpp"

namespace pg {
  class Scene {
  private:
    std::vector<Entity>   m_entities;
    ObjectPooler          m_objectPooler;

  public:
    Scene() {}
    Scene(const Scene& src);

    inline const std::vector<Entity>& GetEntities() const { return m_entities; }
    inline const ObjectPooler& GetObjectPooler() const { return m_objectPooler; }
  };
}
