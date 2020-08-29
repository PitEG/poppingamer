#include "poppingamer/ecs/scene.hpp" 

namespace pg {
  Scene::Scene(std::string name) : m_name(name) {
  }

  Scene::Scene(const Scene& src) {
    m_name = src.m_name;
    m_entities = src.m_entities;
    //object pooler
    m_componentManager = src.m_componentManager;
  }

  Scene::~Scene() {
    /*
     * Delete Components 
     * Delete Entities
     * Delete ObjectPool
     */
  }
}
