#pragma once 

#include <vector>
#include <string>

#include "poppingamer/ecs/entity.hpp"
#include "poppingamer/ecs/objectpooler.hpp"
#include "poppingamer/ecs/componentmanager.hpp"

namespace pg {
  class Scene {
  private:
    std::string           m_name = "scene";
    std::vector<Entity>   m_entities;
    ObjectPooler          m_objectPooler;
    /*
     * Inherit and add the component managers
     */

  public:
    Scene() {}
    virtual ~Scene();

    unsigned int CreateEntity();
    //this probably should be declared in derived scenes
    template<typename T>
    void AddComponent(unsigned int entity, T t);

    virtual bool Disable(unsigned int entity) = 0;
    virtual bool Disable(Entity& entity) = 0;

    inline const std::vector<Entity>& GetEntities() const { return m_entities; }
    inline const ObjectPooler& GetObjectPooler() const { return m_objectPooler; }
  };

  /*
   *
   * EXAMPLE SCENE
   *
   */
  /*
  class ExampleScene : public Scene {
  private:
     //COMPONENTS
    struct Transform {
      float x;
      float y;
    };
    struct Camera {
      float fov;
      int width;
      int height;
    };
  private:
    ComponentManager<Camera> c_cameras;
    ComponentManager<Transform> c_transforms;

  private:
  //SYSTEMS
    void CameraSystem(ComponentManager<Camera>& cameras, ComponentManager<Transform>& transforms) {
      std::vector<unsigned int> entities = cameras.GetEntities();
      for (int i = 0; i < entities.size(); i++) {
        Camera& c = cameras.GetComponent(i);
        Transform& t = transforms.GetComponent(i);
        //nonsense operation
        c.width = t.x;
        c.height = t.y;
      }
    }

  public:

    //UPDATES
    void OnTick() {
      CameraSystem(c_cameras, c_transforms);
    }

    //not necessarily the same as OnTick(). I just don't want to write another example system
    void OnRender() {
      CameraSystem(c_cameras, c_transforms);
    }
  };
*/

}
