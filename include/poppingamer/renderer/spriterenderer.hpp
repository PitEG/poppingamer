#pragma once

#include <SFML/Graphics.hpp>
#include "poppingamer/renderer/renderable.hpp"
#include "poppingamer/renderer/camera.hpp"

#include "poppingamer/ecs/componentmanager.hpp"
#include "poppingamer/ecs/transform.hpp"

/*
 * Uses SFML sprites and vectors
 * SFML has sprites' origins set to the topleft corner of the sprite.
 * The coordinate system has the origin at the top left corner of the screen.
 */

namespace pg {
  class SpriteRenderer : public Renderable {
  private:
    sf::Sprite m_sprite;

  public:
    SpriteRenderer(sf::Sprite sprite, unsigned int layer = 0);
    ~SpriteRenderer();

    void ChangeSprite(const sf::Sprite sprite);
    inline void SetScale(unsigned int scale) { 
      m_sprite.setScale(scale, scale); 
    }

    virtual void Draw(Camera& camera, sf::RenderTexture* rt) override;

    static void UpdatePositions(
        ComponentManager<SpriteRenderer>& spriteRenderers,
        ComponentManager<Transform>& transforms);
  };
}
