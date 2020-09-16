#include "poppingamer/renderer/spriterenderer.hpp"

#include <vector>

namespace pg { 
  SpriteRenderer::SpriteRenderer(sf::Sprite sprite, unsigned int layer) 
  : Renderable(layer, true) {
    m_sprite = sprite;
    //set origin to bottom left of sprite (to match modified coordinate system)
    const sf::FloatRect& rect = m_sprite.getLocalBounds();
    m_sprite.setOrigin(rect.left, rect.height);
  }

  SpriteRenderer::~SpriteRenderer() {
  }

  void SpriteRenderer::Draw(Camera& camera, sf::RenderTexture* rt) {
    rt->setView(camera.view);
    rt->draw(m_sprite);
  }

  //Component Systems
  void SpriteRenderer::UpdatePositions(
      ComponentManager<SpriteRenderer>& spriteRenderers,
      ComponentManager<Transform>& transforms) {

    std::vector<Component<SpriteRenderer>>& spriteComponents 
      = spriteRenderers.GetComponents();

    for(int i = 0; i < spriteComponents.size(); i++) {
      Component<SpriteRenderer>& component = spriteComponents[i];
      //check if sprite has a transform, skip if it doesn't
      if(!transforms.Contains(component.entityID)) { continue; }

      //get sprite and its transform
      Component<SpriteRenderer>& spriteComponent = spriteComponents[i];
      Component<Transform>& transformComponent = 
        transforms.GetComponent(spriteComponent.entityID);
      sf::Sprite& sprite = spriteComponent.component.m_sprite; 
      const sf::Vector2f& position = transformComponent.component.Position(); 

      //set position
      sprite.setPosition(position);
    }
  }
}
