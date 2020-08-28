#pragma once  

#include <vector>
#include <unordered_map>
#include <string>

#include "poppingamer/ecs/component.hpp"
#include "poppingamer/ecs/entity.hpp"
#include "poppingamer/ecs/objectpooler.hpp"

namespace pg {
  class Scene {
  private:
    std::string         m_name;
    std::vector<Entity> m_entities;

    ObjectPooler        m_objectPooler;

  public:
    /*
     * CONSTRUCTORS
     */
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
    inline const std::vector<Entity>& GetEntities() const { return m_entities; }
    inline ObjectPooler& GetObjectPooler() { return m_objectPooler; }

    /*
     * Creates a pool of this entity.
     * Returns true if the name hasn't been taken. false if it has.
     * Also adds to list of entities
     */
    bool PoolEntity(unsigned int amount, Entity& entity, std::vector<Component>& components);
    /*
     * Adds entity to scene and its components to the scene 
     */
    bool AddEntity(Entity& entity, std::vector<Component>& components);

  };
}
