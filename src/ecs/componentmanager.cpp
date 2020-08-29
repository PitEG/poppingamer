#include "poppingamer/ecs/componentmanager.hpp" 

namespace pg {
  template<typename T>
  bool ComponentManager<T>::Create(Entity& e) {
    return Create(e.GetID());
  }

  template<typename T>
  bool ComponentManager<T>::Create(unsigned int e) {
    //if already in map, return false
    if (!Contains(e)) {
      return false;
    }
    //push a component to the list
    T actual_component;
    Component c(actual_component, e, true);
    unsigned int idx = m_components.size();
    m_components.push_back(c);
    m_e2cMap[e] = idx;
    return true;
  }

  template<typename T>
  bool ComponentManager<T>::Contains(unsigned int e) {
    auto itr = m_e2cMap.find(e);
    if (itr == m_e2cMap.end()) {
      return false;
    }

    return true;
  }

  template<typename T>
  T& ComponentManager<T>::GetComponent(unsigned int e) {
    return m_e2cMap[e];
  }

  template<typename T>
  bool ComponentManager<T>::SetActive(unsigned int e, bool active) {
    if (!Contains(e)) {
      return false;
    }

    unsigned int idx = m_e2cMap[e];
    m_components[idx].active = true;
    return true;
  }
  template<typename T>
  bool ComponentManager<T>::SetActive(Entity& e, bool active) {
    return SetActive(e.GetID(), active);
  }
}
