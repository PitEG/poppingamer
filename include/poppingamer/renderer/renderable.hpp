#pragma once 

#include <SFML/Graphics.hpp>

#include <poppingamer/renderer/camera.hpp>

namespace pg {
  class Renderable {
  public:
    Renderable(unsigned int layer) : m_layer(layer) {}

    virtual void Draw() const {}
    virtual void Draw(sf::RenderWindow* window) const {}
    //TODO figure out how to use a render texture, view, window, and camera
    virtual void Draw(Camera& camera, sf::RenderWindow* window) {}
    virtual void Draw(const Camera& camera) {}
    
    inline unsigned int GetLayer() const { return m_layer; }
    inline void SetLayer(unsigned int layer) { m_layer = layer; }

  protected: 
    unsigned int m_layer = -1;
  };
}
