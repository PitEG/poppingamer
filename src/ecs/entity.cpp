#include "poppingamer/ecs/entity.hpp"

namespace pg {
  Entity::Entity(
      Scene* scene, 
      std::string name, 
      bool active, 
      const std::vector<unsigned int>& components) 
    : m_scene(scene), 
    m_name(name), 
    m_active(active), 
    m_components(components) {
  }

  Entity::Entity(const Entity& src, Scene* newScene) 
    : m_scene(newScene), 
    m_name(src.Name()), 
    m_id(src.ID()), 
    m_active(src.GetActive()), 
    m_components(src.GetComponents()) {
  }

  Entity::~Entity() {
  }
}
