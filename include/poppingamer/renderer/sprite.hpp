#pragma once

#include <SFML/Graphics.hpp>

namespace pg {
  class Sprite : public Renderable {
  public:
    Sprite();
    ~Sprite();

    virtual void Draw() override;

  private:
    sf::Sprite m_sprite;
  };
}
