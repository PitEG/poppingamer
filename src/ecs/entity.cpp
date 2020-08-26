#include "poppingamer/ecs/entity.hpp"

namespace pg {
  Entity::Entity(
      Scene* scene, 
      std::string name, 
      bool active, 
      const std::vector<Component*>& components) 
  : m_scene(scene), m_name(name), m_active(active), m_components(components) {
  }

  Entity::~Entity() {
  }
}
