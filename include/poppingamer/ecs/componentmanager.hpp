#pragma once 

#include <vector>
#include <unordered_map>

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  template<typename T>
  class ComponentManager {
  private:
    struct Component {
      T component;
      bool active;
    };

    std::vector<Component> m_components;
    //std::unordered_map<unsigned int, unsigned int> m_entities; //maps component id to entity id;
    std::vector<unsigned int> m_entities;

  public:
    /*
     * Add a component type associated with e
     */
    void Create(Entity& e);

    /*
     * Get list of entity id's
     */
    inline const std::vector<unsigned int>& GetEntities() const { return m_entities; }

    /*
     * Get component of specified entity (via id)
     */
    T& GetComponent(unsigned int entity);


    /*
     * Looks up component (via entity) and disables the component
     */
    inline void Disable(Entity& e) { Disable(e.GetID()); }
    void Disable(unsigned int e);

    /*
     * Looks up component (via entity) and enables the component
     */
    inline void Enable(Entity& e) { Enable(e.GetID()); }
    void Enable(unsigned int e);

  private:
  };
}
