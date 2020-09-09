#include "poppingamer/renderer/spriterenderer.hpp"

namespace pg { 
  SpriteRenderer::SpriteRenderer(sf::Sprite sprite, unsigned int layer) 
  : Renderable(layer, true) {
    m_sprite = sprite;
  }

  SpriteRenderer::~SpriteRenderer() {
  }

  void SpriteRenderer::Draw(Camera& camera, sf::RenderTexture* rt) {
    rt->setView(camera.view);
    rt->draw(m_sprite);
  }
}
