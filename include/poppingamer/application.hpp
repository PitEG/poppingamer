#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 

#include <string>

namespace pg {
  class Application {
  public:
    //set a fixed size window
    Application(int width, int height, std::string name)
    : m_width(width), m_height(height) {
      sf::Uint32 windowStyle = sf::Style::Titlebar | sf::Style::Close; 
      m_window = new sf::RenderWindow(sf::VideoMode(width, height), name, windowStyle); 
      m_renderer = new Renderer(m_window);
    }

    virtual ~Application() {
      delete m_renderer;
    }

    virtual void WindowResize() {}; 

    virtual void Start() {}
    virtual void Run() {}   
    virtual void Stop() {}

  protected:
    //window
    sf::RenderWindow* m_window;
    int               m_width;
    int               m_height;

    //renderer
    Renderer*         m_renderer;
  };
}
