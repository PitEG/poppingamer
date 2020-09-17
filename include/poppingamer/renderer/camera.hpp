#pragma once

#include <SFML/Graphics.hpp>

#include "poppingamer/ecs/componentmanager.hpp"
#include "poppingamer/ecs/transform.hpp"

namespace pg {
  struct Camera {
    sf::View      view;
    unsigned int  zoom;

    Camera() : Camera(sf::Vector2f(0,0), sf::Vector2f(100,100)) {}
    Camera(sf::Vector2f pos, sf::Vector2f size) : view(pos,size) {
      view.setCenter(pos);
      zoom = 1;
    }

    static void UpdatePosition( 
      ComponentManager<Camera>& cameras,
      ComponentManager<Transform>& transforms) {

        std::vector<Component<Camera>>& cameraComponents
          = cameras.GetComponents();

        for(int i = 0; i < cameraComponents.size(); i++) {
          Component<Camera>& component = cameraComponents[i];
          //check if sprite has a transform, skip if it doesn't
          if(!transforms.Contains(component.entityID)) { continue; }

          //get sprite and its transform
          Component<Camera>& cameraComponent = cameraComponents[i];
          Component<Transform>& transformComponent = 
            transforms.GetComponent(cameraComponent.entityID);
          sf::View& view = cameraComponent.component.view; 
          const sf::Vector2f& position = transformComponent.component.Position(); 

          //set position
          view.setCenter(position);
        }
    }
  };
}
