#pragma once

#include <SFML/Graphics.hpp>

#include "poppingamer/ecs/componentmanager.hpp"

namespace pg {
  struct Camera {
    sf::View      m_view;
    unsigned int  m_scale;
    bool          m_active = false;      
  };
}
