#include <poppingamer/poppingamer.hpp>

class TScene : public pg::Scene {
public:
  template<typename T>
  void AddComponent(unsigned int entity, T t) {}

  //might want to write this into the sprierenderer
  std::vector<pg::Renderable*> GetRenderables() {
    unsigned int numRenderables = c_sprites.GetComponents().size();
    auto componentsArray = c_sprites.GetComponents().data();
    std::vector<pg::Renderable*> renderables;
    for (int i = 0; i < numRenderables; i++) {
      renderables.push_back(&(componentsArray[i].component));
    }
    return renderables;
  }

  std::vector<pg::Camera> GetCameras() {
    std::vector<pg::Camera> cameras;
    auto cameraComponents = c_cameras.GetComponents();
    for (int i = 0; i < cameraComponents.size(); i++) {
      cameras.push_back(cameraComponents[i].component);
    }
    return cameras;
  }

  //update pipeline
  void Tick() {
      sf::Vector2f displacement;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        displacement += sf::Vector2f(0,0.05f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        displacement += sf::Vector2f(-0.05f,0);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        displacement += sf::Vector2f(0,-0.05f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        displacement += sf::Vector2f(0.05f,0);
      }
      SystemMoveSybil(displacement);

      sf::Vector2f cdisplacement;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cdisplacement += sf::Vector2f(0,0.05f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        cdisplacement += sf::Vector2f(-0.05f,0);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        cdisplacement += sf::Vector2f(0,-0.05f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        cdisplacement += sf::Vector2f(0.05f,0);
      }
      SystemMoveCamera(displacement);
  }

  void Render() {
    UpdateSprites();
    //UpdateCameras();
  }


  //systems
  void SystemMoveSybil(const sf::Vector2f& displacement) {
    //hardcoded number
    c_transforms.GetComponents()[0].component.Translate(displacement);
  }
  void SystemMoveCamera(const sf::Vector2f& displacement) {
    //hardcoded number
    c_transforms.GetComponents()[1].component.Translate(displacement);
  }

  void UpdateSprites() {
    pg::SpriteRenderer::UpdatePositions(c_sprites, c_transforms);
  }

  void UpdateCameras() {
    pg::Camera::UpdatePosition(c_cameras, c_transforms);
  }

public:
  //components
  pg::ComponentManager<pg::Transform> c_transforms;
  pg::ComponentManager<pg::Camera> c_cameras;
  pg::ComponentManager<pg::SpriteRenderer> c_sprites;

};

template<>
void TScene::AddComponent<pg::Transform>(unsigned int entity, pg::Transform t) {
  c_transforms.Create(entity, t);
}

template<>
void TScene::AddComponent<pg::Camera>(unsigned int entity, pg::Camera c) {
  c_cameras.Create(entity, c);
}

template<>
void TScene::AddComponent<pg::SpriteRenderer>(unsigned int entity, pg::SpriteRenderer s) {
  c_sprites.Create(entity, s);
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
  App() : App(320, 180, "app") {
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
    sybilTransform.Translate(20,-30);
    pg::SpriteRenderer sybilSprite(m_spritelibrary.Get("sybil"), 1);
    sybilSprite.SetScale(1);
    scene_titlemenu.AddComponent<pg::Transform>(sybil.GetID(), sybilTransform);
    scene_titlemenu.AddComponent<pg::SpriteRenderer>(sybil.GetID(), sybilSprite);

    pg::Entity camera;
    pg::Transform cameraTransform;
    sf::Vector2u cameraSize = m_window->getSize();
    pg::Camera cameraCamera(
        sf::Vector2f(0,0), sf::Vector2f(cameraSize.x, cameraSize.y));
    scene_titlemenu.AddComponent<pg::Transform>(camera.GetID(), cameraTransform);
    scene_titlemenu.AddComponent<pg::Camera>(camera.GetID(), cameraCamera);

    //load initial scene
    scene_current = scene_titlemenu;
  }

  virtual void Stop() override {
  }

  virtual void Run() override {
    //create render textures
    sf::RenderTexture rt_lowRes;
    rt_lowRes.create(m_window->getSize().x, m_window->getSize().y);
    std::vector<sf::RenderTexture*> renderTextures;
    renderTextures.push_back(&rt_lowRes);

    //game loop
    while(m_window->isOpen()) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_window->close();
      }
      scene_current.Tick();
      scene_current.Render();

      //render
      std::vector<pg::Camera> cameras = scene_current.GetCameras();
      std::vector<pg::Renderable*> renderables= scene_current.GetRenderables();

      m_renderer->PushCameras(cameras, renderTextures);
      m_renderer->PushRenderables(renderables);
      m_renderer->Draw();

      m_window->display();
    }
  }
};

int main() {
  {
  App app;

  app.Start();
  app.Run();
  app.Stop();
  }

  return 0;
}

/*
 * List of Things I want to do
 *
 * - Resize window event (have renderer be aware of this too)
 * - Sound Library
 * - Music Library
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