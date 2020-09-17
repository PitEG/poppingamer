#include "poppingamer/spritelibrary.hpp"

namespace pg {
  bool SpriteLibrary::Contains(std::string name) {
    auto itr = m_sprites.find(name);
    if (itr == m_sprites.end()) {
      return false;
    }
    return true;
  }

  bool SpriteLibrary::AddSprite(std::string name, sf::Sprite& sprite) {
    if (Contains(name)) {
      return false;
    }
    m_sprites[name] = sprite;
    return true;
  }
  bool SpriteLibrary::AddSprite(std::string name, std::string filepath) {
    //TODO "nonconsequential" memory leak
    sf::Texture* texture = new sf::Texture;
    texture->loadFromFile(filepath);
    sf::Sprite sprite(*texture);
    return AddSprite(name, sprite);
  }

  bool SpriteLibrary::Get(std::string name, sf::Sprite& sprite) {
    if (!Contains(name)) {
      return false;
    }
    sprite = m_sprites[name];
    return true;
  }

  sf::Sprite SpriteLibrary::Get(std::string name) {
    if (Contains(name)) {
      return m_sprites[name];
    }
    sf::Sprite sprite;
    return sprite;
  }
}
