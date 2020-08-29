#pragma once  

namespace pg {
  class Component {
  private:
    unsigned int  m_entityId;
    bool          m_active;

  public:
    Component() : Component(-1, false) {}
    Component(unsigned int entity, bool active = true) 
      : m_entityId(entity), m_active(active) {}
    Component(const Component& src) {
      m_entityId = src.m_entityId;
      m_active = src.m_active;
    }
    virtual ~Component() {} 

    /* GAME LOGIC
     * this is flow of how components are run
     */
    virtual void OnStart() {}     //when component is created
    virtual void OnEnable() {}    //when component is enabled 

    virtual void OnTick() {}      //on game logic tick
    virtual void OnRender() {}    //when frame is rendering 

    virtual void OnDisable() {}   //when component is disabled

    /*
     * Methods
     */
    inline void SetActive(bool active) { m_active = active; OnDisable(); }

    inline const bool GetActive() const { return m_active; }
    inline const unsigned int GetEntity() const { return m_entityId; }
  };
} 
