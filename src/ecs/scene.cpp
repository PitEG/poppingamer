#include "poppingamer/ecs/scene.hpp" 

namespace pg {
  Scene::Scene(std::string name) : m_name(name) {
  }

  Scene::~Scene() {
    /*
     * Delete Components 
     * Delete Entities
     * Delete ObjectPool
     */
  }
}
