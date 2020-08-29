#include "poppingamer/ecs/objectpooler.hpp" 

namespace pg {
  ObjectPooler::ObjectPooler() {
  }

  bool ObjectPooler::AddPool(
      const std::vector<Entity>& entities, 
      const std::string& identifier) { 
    //check if hash value is already associated with a pool
    auto itr = m_pools.find(identifier);
    if (itr != m_pools.end()) {
      //return false if hash value is used
      return false;
    }
    //insert new pool into the map
    Pool pool(identifier, entities);
    m_pools[identifier] = pool;

    return true;
  }

  unsigned int ObjectPooler::GetEntity(std::string name) {
    auto itr = m_pools.find(name);
    if (itr == m_pools.end()) {
      return -1;
    }
    
    Pool& pool = itr->second;
    return pool.GetNext();
  }

  ObjectPooler::Pool::Pool(const std::string identifier, const std::vector<Entity>& entities) 
  : m_name(identifier), m_nextIdx(0) {
    for (int i = 0; i < entities.size(); i++) {
      m_entities.push_back(entities[i].GetID());
    }
  }

} 
