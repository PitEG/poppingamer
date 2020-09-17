#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

namespace pg { 
  class SpriteLibrary {
  private:
    std::unordered_map<std::string, sf::Sprite> m_sprites;
  public:
    bool Contains(std::string name);

    //add sprite by copying
    bool AddSprite(std::string name, sf::Sprite& sprite);
    //add sprite by file location 
    bool AddSprite(std::string name, std::string filelocation);

    //get copy of sprite
    //out var: sprite
    bool Get(std::string name, sf::Sprite& sprite);
    sf::Sprite Get(std::string name);
  };
}
