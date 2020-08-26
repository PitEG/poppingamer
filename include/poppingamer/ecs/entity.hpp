#pragma once 

#include <vector>

#include "poppingamer/ecs/scene.hpp"
#include "poppingamer/ecs/component.hpp"

namespace pg { 
  class Scene;
  class Component;

  class Entity { 
  public:
    Entity(Scene* scene, std::string name = "entity", bool active = true, const std::vector<Component*>& components = std::vector<Component*>()); 
    ~Entity();

    inline const std::string& Name() const { return m_name; }
    inline const Scene* GetScene() const { return m_scene; }
    inline const std::vector<Component*>& GetComponents() const { return m_components; }

    inline const bool GetActive() const { return m_active; }
    inline void SetActive(bool active) { m_active = active; } 

  private:
    Scene*                  m_scene;
    std::string             m_name;
    bool                    m_active;
    std::vector<Component*> m_components;

  };
}
