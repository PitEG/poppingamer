#pragma once

#include <SFML/Graphics.hpp>

#include "poppingamer/ecs/componentmanager.hpp"

namespace pg {
  struct Camera {
    sf::View      view;
    Camera() : Camera(sf::Vector2f(0,0), sf::Vector2f(100,100)) {}
    Camera(sf::Vector2f pos, sf::Vector2f size) : view(pos,size) {
      view.setCenter(pos);
    }
    
  };
}
