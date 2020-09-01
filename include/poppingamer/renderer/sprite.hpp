#pragma once

#include <SFML/Graphics.hpp>

namespace pg {
  class SpriteRenderer : public Renderable {
  private:
    sf::Sprite m_sprite;

  public:
    Sprite();
    Sprite(sf::Sprite sprite, unsigned int layer = 0);

    void ChangeSprite(const sf::Sprite sprite);

    virtual void Draw(Camera& camera, sf::RenderTexture* rt) override;
    virtual void Draw(Camera& camera, sf::RenderWindow* window) override;

  };
}
