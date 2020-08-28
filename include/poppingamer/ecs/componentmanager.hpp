#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <iostream>

#include "poppingamer/ecs/component.hpp"

namespace pg {
  class ComponentManager {
  private:
    std::unordered_map<std::type_index, std::vector<Component>*> m_components;

  public:
    /*
     * CONSTRUCTORS
     */
    ComponentManager() {}
    //copy constructor
    ComponentManager(ComponentManager* cm_target, void (*copy)(ComponentManager*, ComponentManager*)) {
      copy(cm_target, this); 
    }

    /*
    ComponentManager(ComponentManager& cm) {
      //iterate over every element in cm
         auto itr = cm.m_components.begin();
         while( itr != cm.m_components.end()) {
         std::vector<Component>* originalCompList = 
         cm.m_components[itr->first];
         std::vector<Component>* newCompList = 
         new std::vector<Component>(*originalCompList);
         m_components[itr->first] = newCompList;
         itr++;
      }
    }
    */

    //ADD COMPONENT
    template<class T>
    bool AddComponents(const std::vector<T>& components) {
      static int run = 0;
      //go look through m_components
      auto itr = m_components.find(typeid(T));
      std::vector<T>* compList = NULL;
      if (itr == m_components.end()) {
        std::vector<T>* newCompList = new std::vector<T>();
        m_components[typeid(T)] = (std::vector<Component>*)newCompList;
        compList = newCompList;
      }
      else {
        compList = (std::vector<T>*)itr->second;
      }
      for (int i = 0; i < components.size(); i++) {
        compList->push_back(components[i]);
      }
      return true;
    }

    //GET A COPY OF A COMPONENT LIST 
    template<class T>
    std::vector<T> CopyComponentList() {
      auto itr = m_components.find(typeid(T));
      if (itr == m_components.end()) {
        return std::vector<T>();
      }
      //std::vector<T> cList = *((std::vector<T>*)itr->second);
      auto cList = (std::vector<T>*)(m_components[typeid(T)]);
      return *cList;
    }

    //TICK COMPONENT
    template<class T>
    bool Tick() {
      auto itr = m_components.find(typeid(T));
      if (itr == m_components.end()) {
        return false;
      }
      std::vector<Component>* compList = m_components[typeid(T)];
      for (int i = 0; i < compList->size(); i++) {
        Component& c = (*compList)[i];
        c.OnTick();
      }
      return true;
    }
  };
}
