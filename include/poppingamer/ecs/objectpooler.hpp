#pragma once 

#include <unordered_map>
#include <vector>
#include <string>

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  class Entity; 

  class ObjectPooler {
  private:
    struct Pool; //pool declaration
    std::unordered_map<std::string, Pool*> m_pools;

  public:
    ObjectPooler();
    ~ObjectPooler();

    bool AddPool(const std::vector<Entity*>& entities, const std::string& identifier); 
    /*
     * Returns the entity from its pool by the identifier string. If the
     * pool does not exist (ie: the identifier is not mapped to a pool),
     * it returns NULL.
     */
    Entity* GetEntity(std::string name); 

  //START POOL
  private:
    struct Pool {
    public:
      Pool(std::string identifier, const std::vector<Entity*>& entities);

      inline const std::vector<Entity*>& GetEntities() const { return m_entities; }
      inline Entity* GetNext() { 
        Entity* returnEntity = m_entities[m_nextIdx++]; 
        if (m_nextIdx >= m_entities.size()) {
          m_nextIdx = 0;
        }
        return returnEntity;
      }

    private:
      unsigned int          m_nextIdx = 0;
      std::vector<Entity*>  m_entities;
      std::string           m_name; //identifier
    }; //END POOL

  }; //END OBJECTPOOL
}
