#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 


namespace pg {
  class Application {
  public:
    Application();
    ~Application();

    virtual void Start() = 0;
    virtual void Run()   = 0;
    virtual void Stop()  = 0;

  protected:
    sf::RenderWindow m_window;
  };
}
