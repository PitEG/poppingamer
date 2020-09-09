#pragma once

#include <SFML/Graphics.hpp>
#include "poppingamer/renderer/renderable.hpp"
#include "poppingamer/renderer/camera.hpp"

namespace pg {
  class SpriteRenderer : public Renderable {
  private:
    sf::Sprite m_sprite;

  public:
    SpriteRenderer(sf::Sprite sprite, unsigned int layer = 0);
    ~SpriteRenderer();

    void ChangeSprite(const sf::Sprite sprite);

    virtual void Draw(Camera& camera, sf::RenderTexture* rt) override;
    /*
    virtual void Draw(Camera& camera, sf::RenderWindow* window) override;
    */

  };
}
