#pragma once 

#include <vector>
#include <unordered_map>

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  template<typename T>
  class ComponentManager {
  public:
    struct Component {
      T component; //the actual component
      unsigned int entityId;
      bool active;

      Component(T c, unsigned int entityId, bool active) 
        : component(c), entityId(entityId), active(active) {
      }
    };

  private:
    typedef std::unordered_map<unsigned int, unsigned int> e_to_c;

    e_to_c                  m_e2cMap; //maps entity id to component
    std::vector<unsigned int>  m_entities;
    std::vector<Component>  m_components;

  public:
    /*
     * Get list of entity id's
     */
    inline std::vector<unsigned int> GetEntities() { return m_entities; }

    /*
     * Get reference to the list of Components
     */
    inline std::vector<Component>& GetComponents() { return m_components; }

    /*
     * Add a component type associated with e. Only one component per
     * entity;
     */
    bool Create(Entity& e, T component = T()) {
      return Create(e.GetID(), component);
    }
    bool Create(unsigned int e, T component = T()) {
      //if already in map, return false
      if (Contains(e)) {
        return false;
      }
      //push a component to the list
      Component c(component, e, true);
      unsigned int idx = m_components.size();
      m_components.push_back(c);
      m_e2cMap[e] = idx;
      return true;
    }

    /*
     * Check if entity contains this kind component
     */
    bool Contains(unsigned int e) {
      auto itr = m_e2cMap.find(e);
      if (itr == m_e2cMap.end()) {
        return false;
      }

      return true;
    }

    /*
     * Get component of specified entity (via id). Will have 
     * unexpected behavior if component doesn't exist
     */
    Component& GetComponent(unsigned int e) {
      return m_components[m_e2cMap[e]];
    }

    /*
     * Looks up component (via entity) and enable/disables the component
     */
    bool SetActive(unsigned int e, bool active) {
      if (!Contains(e)) {
        return false;
      }

      unsigned int idx = m_e2cMap[e];
      m_components[idx].active = true;
      return true;
    }
    bool SetActive(Entity& e, bool active) {
      return SetActive(e.GetID(), active);
    }
  };
}
