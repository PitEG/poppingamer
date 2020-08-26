#pragma once  

#include <vector>
#include <string>

#include "poppingamer/ecs/entity.hpp"
#include "poppingamer/ecs/objectpooler.hpp"

namespace pg {
  class Entity;
  class ObjectPooler;

  class Scene {
  public:
    Scene(std::string name = std::string("scene"));
    ~Scene();

    inline const std::string& Name() const { return m_name; }
    inline const std::vector<Entity*>* GetEntities() const { return m_entities; }

  private:
    std::string           m_name;
    std::vector<Entity*>* m_entities;

    ObjectPooler*         m_objectPooler;
  };
}
