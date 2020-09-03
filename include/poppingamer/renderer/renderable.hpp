#pragma once 

#include <SFML/Graphics.hpp>

#include <poppingamer/renderer/camera.hpp>

namespace pg {
  class Renderable {
  protected: 
    //IMPORTANT
    unsigned int m_layer = -1;
    bool         m_active = true;

  public:
    bool m_shouldRender = false;
    Renderable() {}
    Renderable(unsigned int layer, bool shouldRender) 
      : m_layer(layer), m_shouldRender(true) {}

    virtual void Draw(Camera& camera, sf::RenderTexture* rt) {}
    virtual void Draw(Camera& camera, sf::RenderWindow* window) {}
    
    inline unsigned int GetLayer() const { return m_layer; }
    inline bool GetActive() const { return m_active; }
    inline void SetLayer(unsigned int layer) { m_layer = layer; }
  };
}
