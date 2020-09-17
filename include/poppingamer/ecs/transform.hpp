#pragma once

#include <SFML/Graphics.hpp>

namespace pg {
  struct Transform {
  private:
    sf::Vector2f position = sf::Vector2f(0,0);

  public:
    float rotation = 0.0f;

    inline sf::Vector2f Position() const {
      sf::Vector2f currPosition(position.x, position.y);
      return currPosition;
    }

    //flipping to fit a more standard coordinate system
    void Translate(float x, float y) {
      Translate(sf::Vector2(x,y));
    }

    void Translate(sf::Vector2f vector) {
      position += sf::Vector2(vector.x, -vector.y);
    }

    void Rotate(float degree) {
      rotation += degree;
    }
  };
}
