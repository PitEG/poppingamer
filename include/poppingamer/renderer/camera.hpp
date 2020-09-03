#pragma once

#include <SFML/Graphics.hpp>

#include "poppingamer/ecs/componentmanager.hpp"

namespace pg {
  struct Camera {
    sf::View      view;
    bool          active = true;      
  };
}
