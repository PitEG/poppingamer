#pragma once

#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 

namespace pg {
  class Transform : public Component {
  public:
    sf::Vector2f position;
    float angle; //in degrees, 0 means no rotation

  public:
    Transform();
    ~Transform();

    void Translate(sf::Vector2f offset);
    void Rotate(float degree); //+ rotates clockwise

  };
}
