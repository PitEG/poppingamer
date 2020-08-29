#pragma once 

#include <string>
#include <vector>
#include <typeinfo>

namespace pg {
  class Entity {

  private:
    unsigned int  m_id;
    std::string   m_name;
    bool          m_active;

  public:
    Entity(const unsigned int id = -1, const std::string name = "entity") 
      : m_id(id), m_name(name), m_active(true) {
    }
    Entity(const Entity& entity); //copy constructor

    inline const std::string& GetName() const { return m_name; }
    inline const unsigned int GetID() const { return m_id; }
  };
}
