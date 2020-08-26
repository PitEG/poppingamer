#include "poppingamer/ecs/objectpooler.hpp" 

namespace pg {
  ObjectPooler::ObjectPooler() {
  }

  ObjectPooler::~ObjectPooler() {
  }

  bool ObjectPooler::AddPool(
      const std::vector<Entity*>& entities, 
      const std::string& identifier) { 
    //check if hash value is already associated with a pool
    auto itr = m_pools.find(identifier);
    if (itr != m_pools.end()) {
      //return false if hash value is used
      return false;
    }
    //insert new pool into the map
    Pool* pool = new Pool(identifier, entities);
    m_pools[identifier] = pool;

    return true;
  }

  Entity* ObjectPooler::GetEntity(std::string name) {
    auto itr = m_pools.find(name);
    if (itr == m_pools.end()) {
      return NULL;
    }
    
    Pool* pool = m_pools[name];
    return pool->GetNext();
  }

  ObjectPooler::Pool::Pool(std::string identifier, const std::vector<Entity*>& entities) 
  : m_name(identifier), m_entities(entities), m_nextIdx(0) {
  }
}

