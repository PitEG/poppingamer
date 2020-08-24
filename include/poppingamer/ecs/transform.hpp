#pragma once

#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 

namespace pg {
  class Transform : public Component {
  public:
    sf::Vector2<float> position;
    float angle; //in degrees, 0 means no rotation

  public:
    Transform();
    ~Transform();


    void Translate(sf::Vector2<float> offset);
    void Rotate(float degree); //+ rotates clockwise

  };
}
