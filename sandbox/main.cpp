#include <poppingamer/poppingamer.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <string>
#include <iostream>

class RDR : public pg::Renderable {
public:
  RDR() : RDR(1) {}
  RDR(unsigned int layer) 
  : pg::Renderable(layer), rs(sf::Vector2f(10,10)){
  }
  virtual void Draw(const pg::Camera& camera) {
    sf::RenderTexture* rt = camera.m_rTexture;
    rt->draw(rs);
  }
  sf::RectangleShape rs;
};

class App : public pg::Application {
public:
  App(int width, int height, std::string name)
  : pg::Application(width, height, name) {
  }

  virtual void Start() override {
  }
  virtual void WindowResize() override {
  }

  virtual void Run() override {
    RDR rdr(10);
    RDR rdr2(11);
    RDR rdr3(10);
    int randNum = 1000;
    RDR* rand = new RDR[randNum];

    rdr.rs.setFillColor(sf::Color(240, 230, 0));
    rdr2.rs.setFillColor(sf::Color(100, 100, 100));
    rdr2.rs.setPosition(rdr2.rs.getPosition() + sf::Vector2f(1.f,1.f));
    rdr3.rs.setFillColor(sf::Color(0, 190, 0));
    rdr3.rs.setPosition(rdr2.rs.getPosition() + sf::Vector2f(4.f,4.f));

    int w = m_window->getSize().x / 3;
    int h = m_window->getSize().y / 3;
    sf::RenderTexture rt;
    rt.create(w,h);
    sf::RenderTexture rt2;
    rt2.create(w,h);

    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(w, h));
    sf::View view2(sf::Vector2f(30, 10), sf::Vector2f(w, h));

    std::vector<pg::Renderable*> renderables(pg::Renderer::INITIAL_LAYER_LIST_SIZE, 0);

    //framerate
    m_window->setFramerateLimit(0);
    m_window->setVerticalSyncEnabled(false);
    unsigned int frame = 0;
    sf::Clock clock;
    sf::Int64 framerate = 120;
    sf::Int64 frametime = 1'000'000 / framerate;
    sf::Int64 lastFrameTime = clock.getElapsedTime().asMicroseconds();
    while (m_window->isOpen()) {
      if (m_window->hasFocus()) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_window->close();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rdr.rs.move(1.f,0.f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rdr.rs.move(-1.f,0.f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        rdr.rs.move(0.f,-1.f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        rdr.rs.move(0.f,1.f);
      }
      }

      //Render
      pg::Camera camera(NULL, view, &rt, 3);
      pg::Camera camera2(NULL, view2, &rt2, 3);

      pg::Camera cameras[10] = {camera,camera2}; 
      renderables[1] = &rdr;
      renderables[2] = &rdr2;
      renderables[0] = &rdr3;

      for (int i = 3; i < randNum; i++) {
        RDR* rP = rand + i;
        if (i >= renderables.size()) {
          renderables.push_back(rP);
        }
        else {
          renderables[i] = rP;
        }
      }
      m_renderer->PushRenderables(renderables);
      m_renderer->PushCameras(cameras);
      m_renderer->Draw();

      //framerate
      frame++;
      while(clock.getElapsedTime().asMicroseconds() - lastFrameTime < frametime);
      lastFrameTime = clock.getElapsedTime().asMicroseconds();
      std::cout << "time: " << lastFrameTime / (float)1000'000 << "s; frame: " << frame << std::endl;
    }
  }

  virtual void Stop() override {
  }
};

int main() {
  int width  = 520;
  int height = 810;
  App app(width, height, "What's Poppin, Gamer?");
  app.Start();
  app.Run();
  app.Stop();
}
