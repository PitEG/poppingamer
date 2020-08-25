#pragma once  

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  class Entity;

  class Component {
  private:
    Entity* m_entity;
    bool    m_active;

  protected:
    Component(Entity* owner) {}
    ~Component() {}

    /* GAME LOGIC
     * this is flow of how components are run
     */
    virtual void OnStart() {}     //when component is created
    virtual void OnEnable() {}    //when component is enabled 

    virtual void OnTick() {}      //on game logic tick
    virtual void OnRender() {}    //when frame is rendering 

    virtual void OnDisable() {}   //when component is disabled

    inline void SetActive(bool active) { m_active = active; OnDisable(); }

    inline const bool GetActive() const { return m_active; }
    inline const Entity* GetEntity() const { return m_entity; }
  };
}
