#include <poppingamer/poppingamer.hpp> 
#include <SFML/System.hpp> 

#include <string>

//
// COMPONENTS
//
struct Transform {
  float x;
  float y;

  Transform() : x(0), y(0) {}
  Transform(float x, float y) : x(x), y(y) {}

  void Translate(float x_delta, float y_delta) {
    x += x_delta;
    y += y_delta;
  }
};

struct Collider {
  sf::Rect<float> box;

  Collider() : box(sf::Rect<float>()) {}
};

struct Rectangle : public pg::Renderable {
  sf::RectangleShape rs;

  Rectangle() 
  : pg::Renderable(1, true) {
    rs.setFillColor(sf::Color::White);
    rs.setSize(sf::Vector2f(1,1));
  }

  virtual void Draw(pg::Camera& camera, sf::RenderTexture* rt) override {
    rt->setView(camera.view);
    rt->draw(rs);
  }

};

//
// SCENE
//
class RendScene : public pg::Scene {
private:
  pg::ComponentManager<Transform> c_transforms;
  pg::ComponentManager<Collider> c_colliders;
  pg::ComponentManager<pg::Camera> c_cameras;
  pg::ComponentManager<Rectangle> c_rectangles;
  pg::ComponentManager<pg::SpriteRenderer> c_spriteRenderer;

public:
  RendScene() {}
  virtual ~RendScene() {}

  template<typename T>
  void AddComponent(unsigned int entity, T t) {}

  virtual bool Disable(unsigned int entity) { 
    return false; 
  }

  virtual bool Disable(pg::Entity& entity) {
    return false; 
  }

  //Systems
  void SystemTransformWobble() {
    auto& transforms = c_transforms.GetComponents();
    for (int i = 0; i < transforms.size(); i++) {
      transforms[i].component.x = -transforms[i].component.x;
      transforms[i].component.y = -transforms[i].component.y;
    }
  }

  void SystemRectangles() {
    auto& transforms = c_transforms.GetComponents();
    auto& rectangles = c_rectangles.GetComponents();
    for (int i = 0; i < rectangles.size(); i++) {
      float x = transforms[i].component.x;
      float y = transforms[i].component.y;
      rectangles[i].component.rs.setPosition(x, y);
    }
  }

  void SystemCameras() {
    auto& cameraComponents = c_cameras.GetComponents();
    auto& transformComponents = c_transforms.GetComponents();
    for (int i = 0; i < cameraComponents.size(); i++) {
      auto& cameraComponent = cameraComponents[i];
      unsigned int entity = cameraComponent.entityId;
      //check if camera has a transform, skip if not
      if (!c_transforms.Contains(entity)) {
        continue;
      }
      auto& transformComponent = c_transforms.GetComponent(entity);
      Transform& transform = transformComponent.component;
      pg::Camera& camera = cameraComponent.component;
      camera.view.setCenter(transform.x, transform.y);
    }
  }

  void SystemMove(sf::Vector2f displacement) {
    auto& transformComponents = c_transforms.GetComponents();
    for (int i = 0; i < transformComponents.size(); i++) {
      if (!transformComponents[i].active) { continue; }
      if (c_cameras.Contains(transformComponents[i].entityId)) { continue; }
      Transform& transform = transformComponents[i].component;
      transform.Translate(displacement.x, displacement.y);
    }
  }

  //cameras: out var
  void GetCameras(pg::Camera cameras[10]) {
    auto& cameraComponents = c_cameras.GetComponents();
    for (int i = 0; i < cameraComponents.size(); i++) {
      cameras[i] = cameraComponents[i].component;
    }
  }

  std::vector<pg::Camera> GetCams() {
    auto& cameraComponents = c_cameras.GetComponents();
    std::vector<pg::Camera> cameras;
    for (int i = 0; i < cameraComponents.size(); i++) {
      if (!cameraComponents[i].active) { continue; }
      cameras.push_back(cameraComponents[i].component);
    }
    return cameras;
  }

  std::vector<pg::Renderable*> GetRenderables() {
    auto& rectangleComponents = c_rectangles.GetComponents();
    auto& spritesComponents = c_spriteRenderer.GetComponents();
    std::vector<pg::Renderable*> renderables;
    //rectangles
    pg::Component<Rectangle>* rectangles = 
      rectangleComponents.data();
    for (int i = 0; i < rectangleComponents.size(); i++) {
      renderables.push_back(&(rectangles[i].component));
    }
    //sprites
    pg::Component<pg::SpriteRenderer>* sprites = 
      spritesComponents.data();
    for (int i = 0; i < rectangleComponents.size(); i++) {
      renderables.push_back(&(sprites[i].component));
    }
    return renderables;
  }

};

template<>
void RendScene::AddComponent<Transform>(unsigned int entity, Transform t) {
  c_transforms.Create(entity, t);
}
template<>
void RendScene::AddComponent<Collider>(unsigned int entity, Collider t) {
  c_colliders.Create(entity, t);
}

template<>
void RendScene::AddComponent<pg::Camera>(unsigned int entity, pg::Camera t) {
  c_cameras.Create(entity, t);
}

template<>
void RendScene::AddComponent<Rectangle>(unsigned int entity, Rectangle t) {
  c_rectangles.Create(entity, t);
}

template<>
void RendScene::AddComponent<pg::SpriteRenderer>(unsigned int entity, pg::SpriteRenderer sr) {
  c_spriteRenderer.Create(entity, sr);
}

class App : public pg::Application {
private:
  RendScene          m_rscene;
  std::vector<sf::RenderTexture*> m_renderTextures;
  pg::SpriteLibrary  m_spriteLibrary;

public:
  App(int width, int height, std::string name) 
  : pg::Application(width, height, name) {

    //this is an arbitrary number :P
    for(int i = 0; i < 10; i++ ) {
      m_renderTextures.push_back(new sf::RenderTexture());
      m_renderTextures[i]->create(width / 2, height / 2);
    }

  }

  virtual void Start() override {
    //sprite library
    m_spriteLibrary.AddSprite("sybil", "sybilsprite.png");

    auto e0 = m_rscene.CreateEntity("entity 0");
    auto e1 = m_rscene.CreateEntity("entity 1");
    auto e2 = m_rscene.CreateEntity("camera 0");
    auto e3 = m_rscene.CreateEntity("entity 3");

    Transform t0(1,1);
    Transform t1(1,-10);
    Transform t2(1,10);
    Rectangle r0;
    Rectangle r1;
    pg::Camera c0(sf::Vector2f(0,0), sf::Vector2f(m_width / 2, m_height / 2));
    sf::Sprite sybilSprite; 
    m_spriteLibrary.Get("sybil", sybilSprite);
    pg::SpriteRenderer sprite(sybilSprite, 30);

    m_rscene.AddComponent<Transform>(e0, t0);
    m_rscene.AddComponent<Transform>(e1, t1);
    m_rscene.AddComponent<Rectangle>(e0, r0);
    m_rscene.AddComponent<Rectangle>(e1, r1);

    m_rscene.AddComponent<pg::Camera>(e2, c0);
    m_rscene.AddComponent<Transform>(e2, t0);

    m_rscene.AddComponent<pg::SpriteRenderer>(e3,sprite);
  }

  virtual void Run() override {
    sf::Clock clock;
    sf::Int64 fps = 60;
    sf::Int64 frameTime = 1 * 1'000'000 / fps;
    sf::Time sframeTime = sf::microseconds(frameTime);
    while(m_window->isOpen()) {
      //input
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        m_window->close();;
      }
      sf::Vector2f displacement;
      float speed = 0.1f;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        displacement += sf::Vector2f(0,-speed);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        displacement += sf::Vector2f(0,speed);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        displacement += sf::Vector2f(-speed,0);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        displacement += sf::Vector2f(speed,0);
      }

      //game logic
      //copy scene //TODO causes a segfault?
      //RendScene rscene_copy = m_rscene;
      m_rscene.SystemCameras();
      m_rscene.SystemRectangles();
      m_rscene.SystemMove(displacement);

      //render
      std::vector<pg::Camera> cameras = m_rscene.GetCams();
      m_renderer->PushCameras(cameras, m_renderTextures);
      std::vector<pg::Renderable*> renderables = m_rscene.GetRenderables();
      m_renderer->PushRenderables(renderables);
      m_renderer->Draw();

      //swap framebuffer
      m_window->display();

      //might be inaccurate. lowering the framerate by like 2-3 frames
      sf::Time time = clock.getElapsedTime();
      sf::sleep(sframeTime);
    }
  }

  virtual void Stop() override {
  }
};

int main() {
  App app(480, 270, "test_rend");
  app.Start();
  app.Run();
  app.Stop();

  return 0;
}
