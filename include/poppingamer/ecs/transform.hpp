#pragma once

#include <SFML/Graphics.hpp>

namespace pg {
  struct Transform {
  private:
    sf::Vector2f position = sf::Vector2f(0,0);

  public:
    float rotation = 0.0f;

    inline sf::Vector2f Position() const {
      sf::Vector2f position(position.x, position.y);
      return position;
    }

    //flipping to fit a more standard coordinate system
    void Translate(float x, float y) {
      Translate(sf::Vector2(x,-y));
    }

    void Translate(sf::Vector2f vector) {
      position += vector;
    }

    void Rotate(float degree) {
      rotation += degree;
    }
  };
}
