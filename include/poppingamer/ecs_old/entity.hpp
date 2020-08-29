#pragma once 

#include <vector>

namespace pg { 
  class Scene;

  class Entity { 
  private:
    Scene*                     m_scene;
    std::string                m_name;
    unsigned int               m_id;
    bool                       m_active;
    std::vector<unsigned int>  m_components;

  public:
    /*
     * CONSTRUCTORS
     */
    Entity(Scene* scene, std::string name = "entity", bool active = true, const std::vector<unsigned int>& components = std::vector<unsigned int>()); 
    //copy constructor
    Entity(const Entity& entity, Scene* newScene = NULL);
    ~Entity();

    /*
     * GETTERS
     */
    inline const std::string& Name() const { return m_name; }
    inline const unsigned int ID() const { return m_id; }
    inline const Scene* GetScene() const { return m_scene; }
    inline const std::vector<unsigned int>& GetComponents() const { return m_components; }
    inline const bool GetActive() const { return m_active; }

    /*
     * SETTERS
     */
    inline void SetComponents(std::vector<unsigned int> componentIds) { m_components = componentIds; }
    inline void SetActive(bool active) { m_active = active; } 

  };
}
