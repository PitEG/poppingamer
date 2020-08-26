#include "poppingamer/ecs/scene.hpp" 

namespace pg {
  Scene::Scene(std::string name) : m_name(name) {
    m_entities = new std::vector<Entity>;
    m_objectPooler = new ObjectPooler();
  }

  Scene::~Scene() {
    /*
     * Delete Components 
     * Delete Entities
     * Delete ObjectPool
     */

  }
}
