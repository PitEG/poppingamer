#pragma once  

#include <vector>
#include <string>

#include "poppingamer/ecs/component.hpp"
#include "poppingamer/ecs/componentsystem.hpp"
#include "poppingamer/ecs/entity.hpp"
#include "poppingamer/ecs/objectpooler.hpp"

namespace pg {
  class Component;
  class Entity;
  class ObjectPooler;

  class Scene {
  private:
    std::string               m_name;
    std::vector<Entity>*      m_entities;
    std::vector<Component>*   m_components;

    ObjectPooler*             m_objectPooler;
    ComponentSystem           m_componentSystem;

  public:
    Scene(std::string name = std::string("scene"));
    /*
     * Copy Constructor
     */
    Scene(const Scene& scene);

    ~Scene();
    
    /*
     * Getters
     */
    inline const std::string& Name() const { return m_name; }
    inline const std::vector<Entity>* GetEntities() const { return m_entities; }
    inline ObjectPooler* GetObjectPooler() { return  m_objectPooler; }

    void RunComponents();
    /*
     * Creates a pool of this entity.
     * Returns true if the name hasn't been taken. false if it has.
     * Also adds to list of entities
     */
    bool PoolEntity(std::string name, Entity& entity);
    /*
     * Adds entity to scene. It's passed by value
     */
    bool AddEntity(Entity& entity, std::vector<Component>& components);

  };
}
