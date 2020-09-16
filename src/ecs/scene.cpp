#include "poppingamer/ecs/scene.hpp" 

namespace pg {
  unsigned int Scene::CreateEntity(std::string name) {
    unsigned int idx = m_entities.size();
    m_entities.push_back(Entity(idx, name));
    return idx;
  }

  //TODO
  bool Scene::PoolEntity(Entity& entity, std::vector<Entity>& entities) {
    return false;
  }
}

