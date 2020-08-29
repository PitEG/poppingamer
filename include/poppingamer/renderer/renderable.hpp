#pragma once 

#include <SFML/Graphics.hpp>

#include <poppingamer/renderer/camera.hpp>

namespace pg {
  class Renderable {
  protected: 
    //IMPORTANT
    unsigned int m_layer = -1;

  public:
    bool m_shouldRender = false;

    virtual void Draw() const {}
    virtual void Draw(Camera& camera, sf::RenderTexture* rt) {}
    virtual void Draw(Camera& camera, sf::RenderWindow* window) {}
    
    inline unsigned int GetLayer() const { return m_layer; }
    inline void SetLayer(unsigned int layer) { m_layer = layer; }
  };
}
