#pragma once

#include <SFML/Graphics.hpp>

#include "poppingamer/ecs/componentmanager.hpp"

namespace pg {
  struct Camera {
    sf::View            m_view;
    sf::RenderTexture*  m_rTexture; //framebuffer to draw to
    unsigned int        m_scale;
  };

  class CamaraSystem {
  public:
    static void MoveCamera(ComponentManager<Camera> cameras);
  };

}
