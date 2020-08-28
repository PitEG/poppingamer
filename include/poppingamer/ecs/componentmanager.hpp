#pragma once

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <iostream>

#include "poppingamer/ecs/component.hpp"
#include "poppingamer/ecs/updatetypes.hpp"

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
    /*
     * I couldn't figure out a better way. The user must provide a copy
     * constructor with all the different types of compnents.
     * I'll provide an example below it.
     */
    ComponentManager(ComponentManager* cm_src, 
        void (*copy)(const ComponentManager* src, ComponentManager* target)) {
      copy(cm_src, this); 
    }
    /*
    void copyConstructor(pg::ComponentManager* src, pg::ComponentManager* target) {
      std::vector<cTransform>* copiedList = 
        new std::vector<cTransform>(src->CopyComponentList<cTransform>());
      auto list = src->CopyComponentList<cTransform>();
      target->AddComponents<cTransform>(list);
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
    std::vector<T> CopyComponentList() const {
      auto const itr = m_components.find(typeid(T));
      if (itr == m_components.end()) {
        return std::vector<T>();
      }
      //auto cList = (std::vector<T>*)(m_components[typeid(T)]);
      std::vector<T>* cList = (std::vector<T>*)itr->second;
      return *cList;
    }

    //TICK COMPONENT LIST
    /*
     * update the components. Return false if component type T doesn't
     * exist in this manager
     */
    template<class T>
    bool Update(UpdateType updateType) {
      auto itr = m_components.find(typeid(T));
      if (itr == m_components.end()) {
        return false;
      }
      std::vector<Component>* compList = m_components[typeid(T)];
      for (int i = 0; i < compList->size(); i++) {
        Component& c = (*compList)[i];
        switch(updateType) {
          /*
           * To exapnd this, add an enumeration to updatetypes.hpp,
           * modify component.hpp for another virtual update function,
           * and add another case here.
           */
          case(UpdateType::Start)   : c.OnStart(); break;
          case(UpdateType::Tick)    : c.OnTick(); break;
          case(UpdateType::Render)  : c.OnRender(); break;
          case(UpdateType::Enable)  : c.OnEnable(); break;
          case(UpdateType::Disable) : c.OnDisable(); break;
        }
      }
      return true;
    }

  };
}
