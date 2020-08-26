#include <poppingamer/poppingamer.hpp> 

/*
 * Notes on what I want the API to look like for the engine
 */
class App : public pg::Application {
private:
  //SceneManager*       sceneManager;

public:
  //Create a Component System
  class CompSys : public pg::ComponentSystem {
  public:
    virtual void Run() {
      
    }
  }
  //CREATE SCENES + sprites/audio and other resources
  virtual void Start() override {
    //LOAD STUFF
    /* RenderTexture rt[10] = screen resolution
     * Load Sprites
     * Load Audio
     */

    //CREATE SCENES
    /* Entity player = new Entity(player)
     * Entity projectiles = new Entity(projectiles);
     * Entity projectile = new Entity(player)
     * Component projectile_components = {
     *   HealthComponent(10),
     *   ColliderComponent(rectangle),
     *   PhysicsComponent(1),
     * }
     * Scene* scene1 = new Scene();
     * scene1->AddEntity(player);
     * scene1->AddEntity(projectile, projectile_components);
     */
     //create other scenes

  }
  virtual void Run() override {
    /* //RUNNING AT 60FPS
     * while(window.isopen()) {
     * 
     * sceneManager->RunCurrentScene();
     * const Scene* currScene = sceneManager->GetCurrentScene();
     * vector<Renderable*> renderables = currScene->GetRenderables();
     * vector<Camera*> cameras = currScene->GetCameras();
     * 
     * renderer->pushRenderables(renderables);
     * renderer->pushCameras(cameras);
     * renderer->Draw();
     *
     * }
     */
  }
}

int main() {
  /*
   * Application app(1280, 720, "test");
   * app->start();
   * app->run();
   * app->stop()
   */
  return 0;
}
