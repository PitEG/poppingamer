#pragma once 

#include <vector>
#include <string>
#include <unordered_map>

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  class ObjectPooler {
  private:
    struct Pool {
    private:
      std::string               m_name; //identifier
      std::vector<unsigned int> m_entities; //using entity id

      unsigned int        m_nextIdx = 0;

    public:
      Pool() {}
      Pool(const std::string identifier, const std::vector<Entity>& entities);

      inline const std::vector<unsigned int>& GetEntities() const { return m_entities; }
      inline const unsigned int GetNext() { 
        unsigned int returnEntity = m_entities[m_nextIdx++]; 
        if (m_nextIdx >= m_entities.size()) {
          m_nextIdx = 0;
        }
        return returnEntity;
      }
    };

  private:
    std::unordered_map<std::string, Pool> m_pools;

  public:
    ObjectPooler();
    ObjectPooler(const ObjectPooler& op);
    bool AddPool(
        const std::vector<Entity>& entities, 
        const std::string& identifier); 
    /*
     * Returns the entity from its pool by the identifier string. If the
     * pool does not exist (ie: the identifier is not mapped to a pool),
     * it returns NULL.
     */
    unsigned int GetEntity(std::string name); 
  };
}
