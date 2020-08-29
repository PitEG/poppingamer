#pragma once

#include <SFML/Graphics.hpp>

namespace pg {
  class Sprite : public Renderable {
  private:
    sf::Sprite* m_sprite;

  public:
    Sprite();
    Sprite(sf::Sprite* sprite, unsigned int layer = 0);

    void ChangeSprite(sf::Sprite* sprite);

    virtual void Draw(Camera& camera, sf::RenderTexture* rt) override {}
    virtual void Draw(Camera& camera, sf::RenderWindow* window) override {}

  };
}
