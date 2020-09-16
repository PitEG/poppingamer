#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 

#include <string>

namespace pg {
  class Application {
  protected:
    //window
    sf::RenderWindow* m_window;

    //renderer
    Renderer*         m_renderer;
 
  public:
    //set a fixed size window
    Application(int width, int height, std::string name) {
      sf::Uint32 windowStyle = sf::Style::Titlebar | sf::Style::Close; 

      m_window = new sf::RenderWindow(sf::VideoMode(width, height), name, windowStyle); 
      m_renderer = new Renderer(m_window);
    }

    virtual ~Application() {
      delete m_window;
      delete m_renderer;
    }

    virtual void Start() {}
    virtual void Run() {}   
    virtual void Stop() {}

 };
}
