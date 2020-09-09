#pragma once 

#include <vector>
#include <unordered_map>

#include "poppingamer/ecs/entity.hpp"
#include "poppingamer/ecs/component.hpp"

namespace pg {
  template<typename T>
  class ComponentManager {
  private:
    typedef std::unordered_map<unsigned int, unsigned int> e_to_c;

    e_to_c                     m_e2cMap; //maps entity id to component idx (in m_components)
    std::vector<unsigned int>  m_entities; //list of entities
    std::vector<Component<T>>  m_components; //list of components

  public:
    /*
     * Get list of entity id's
     */
    inline std::vector<unsigned int> GetEntities() { return m_entities; }

    /*
     * Get reference to the list of Components
     */
    inline std::vector<Component<T>>& GetComponents() { return m_components; }

    /*
     * Get a list of pointers to active components
     * Just copies the components into a new vector
     */
    inline std::vector<Component<T>*> GetActiveComponents() {
      std::vector<Component<T>*> activeComponents; 
      Component<T>* components = m_components.data();
      for (int i = 0; i < m_components.size(); i++) {
        if (m_components[i].active) {
          activeComponents.push_back(components + i);
        }
      }

      return activeComponents;
    }

    inline int Size() const { return m_components.size(); }

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
      //push entity to entity list
      m_entities.push_back(e);
      return true;
    }

    /*
     * Check if entity contains this kind component
     */
    inline bool Contains(const Entity& e) {
      return Contains(e.GetID());
    }
    bool Contains(unsigned int e) {
      auto itr = m_e2cMap.find(e);
      if (itr == m_e2cMap.end()) {
        return false;
      }

      return true;
    }

    /*
     * Get reference to component of specified entity (via entity id). 
     * Will have unexpected behavior if component doesn't exist; should
     * check if it exists (with Contains()) first.
     */
    Component<T>& GetComponent(unsigned int e) {
      return m_components[m_e2cMap[e]];
    }

    /*
     * Looks up component (via entity id) and enable/disables the component
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
