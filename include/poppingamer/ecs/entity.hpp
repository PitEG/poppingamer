#pragma once 

#include <string>
#include <vector>
#include <typeinfo>

namespace pg {
  class Entity {
  private:
    unsigned int m_id;
    std::string  m_name;
    std::unordered_map<std::type_index, unsigned int> m_components;

  public:
    Entity(const unsigned int id, 
        const std::string name, 
        std::vector<unsigned int> m_components);
    Entity(const Entity& entity);

    template<typename T>
    bool GetComponent(T& c) { 
      auto itr = m_components.find(typeid(T));
      if (itr == m_components.end()) {
        return false;
      }
      c = m_components[typeid(T)];
      return true;
    }

    inline const std::string& GetName() const { return m_name; }
    inline const unsigned int GetID() const { return m_id; }
  };
}
