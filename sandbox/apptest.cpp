#include <poppingamer/poppingamer.hpp>

class TScene : public pg::Scene {
public:
  template<typename T>
  void AddComponent(unsigned int entity, T t) {}

  //might want to write this into the sprierenderer
  std::vector<pg::Renderable*> GetRenderables() {
    unsigned int numRenderables = c_sprites.GetComponents().size();
    auto componentsArray = c_sprites.GetComponents().data();
    std::vector<pg::Renderable*> renderables(numRenderables);
    for (int i = 0; i < numRenderables; i++) {
      renderables.push_back(&(componentsArray[i].component));
    }
    return renderables;
  }

  std::vector<pg::Camera> GetCameras() {
  }

private:
  //components
  pg::ComponentManager<pg::Transform> c_transforms;
  pg::ComponentManager<pg::Camera> c_cameras;
  pg::ComponentManager<pg::SpriteRenderer> c_sprites;

};

template<>
void TScene::AddComponent<pg::Transform>(unsigned int entity, pg::Transform t) {
  c_transforms.Create(entity, t);
}

class App : public pg::Application {
private:
  //scenes
  TScene scene_titlemenu;
  TScene scene_level1;

  TScene scene_current;

  //libraries
  pg::SpriteLibrary m_spritelibrary;

public: 
  App() : App(1280, 720, "app") {
  }

  App(unsigned int width, unsigned int height, std::string name) 
  : pg::Application(width, height, name) {
  }

  virtual ~App() {
  }

  virtual void Start() override {
    //load sprites
    m_spritelibrary.AddSprite("sybil", "sybilsprite.png");

    //create scenes
    pg::Entity sybil;
    pg::Transform sybilTransform;
    pg::Camera camera;
    scene_titlemenu.AddComponent<pg::Transform>(sybil.GetID(), sybilTransform);

    //load current scene
    scene_current = scene_titlemenu;
  }

  virtual void Stop() override {
  }

  virtual void Run() override {
    while(m_window->isOpen()) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_window->close();
      }

      m_window->display();
    }
  }
};

int main() {
  App app;

  app.Start();
  app.Run();
  app.Stop();

  return 0;
}

/*
 * List of Things I want to do
 *
 * - Resize window event (have renderer be aware of this too)
 * - Develop common components that I wish to use often
 *   - Transform
 *   - SpriteRenderer 
 *   - Collision Systems 
 *
 *
 *
 *
 *
 */
