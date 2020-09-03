#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
  sf::RectangleShape rs;
  rs.setPosition(0,0);
  rs.setSize(sf::Vector2f(10,10));
  rs.setFillColor(sf::Color::White);
  sf::View view(sf::Vector2f(0,0), sf::Vector2f(100,100));
  view.setCenter(0,0);
  sf::RenderTexture rt;
  rt.create(480,270);
  sf::RenderWindow window(sf::VideoMode(480,270),"something");

  while(window.isOpen()) {
    window.clear();
    rt.clear(sf::Color::Red);
    rt.setView(view);
    rt.draw(rs);
    sf::Sprite framebuffer(rt.getTexture());
    window.draw(framebuffer);

    window.display();
  }
}
