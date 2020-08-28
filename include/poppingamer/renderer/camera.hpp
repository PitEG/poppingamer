#pragma once

#include <SFML/Graphics.hpp>

#include "poppingamer/ecs/component.hpp"

namespace pg {
  class Camera : public Component {
  public:
    //Entity* entity; from Component
    sf::View            m_view;
    sf::RenderTexture*  m_rTexture; //framebuffer to draw to
    unsigned int        m_scale;

  public:
    /*
     * CONSTRUCTOR
     */
    /*
     * entity:    Entity owner
     * view:      Camera location in the world
     * rt:        framebuffer to draw to
     * scale:     scalar
     */
    Camera(
        sf::View view = sf::View(sf::Vector2f(0,0), sf::Vector2f(100.f,100.f)),
        sf::RenderTexture* rt = NULL,
        unsigned int scale = 1);

    /*
     * Get's the current position of the camera
     */
    const sf::Vector2f GetPosition() const;
    /*
     * Binds the view to the frame buffer
     */
    void BindView();
  };
}
