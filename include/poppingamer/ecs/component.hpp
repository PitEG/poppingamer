#pragma once  

#include "poppingamer/ecs/entity.hpp"

namespace pg {
  class Entity;

  class Component {
  protected:
    Component();

    virtual ~Component();

    /* GAME LOGIC
     * this is flow of how components are run
     */
    virtual void OnStart() {}     //when component is created
    virtual void OnEnable() {}    //when component is enabled 

    virtual void OnTick() {}      //on game logic tick
    virtual void OnRender() {}    //when frame is rendering 

    virtual void OnDisable() {}   //when component is disabled

    void SetActive(bool active);

    inline const bool GetActive() const { return m_active; }
    inline const Entity* GetEntity() const { return m_entity; }

  private:
    Entity* m_entity;
    bool m_active;
  };
}
