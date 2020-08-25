#pragma once  

#include "poppingamer/renderer/renderable.hpp"
#include "poppingamer/renderer/camera.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

namespace pg {
  class Renderer {
  public:
    static const unsigned int MAX_LAYERS = 32;
    static const unsigned int MAX_CAMERAS = 10;
    static const unsigned int INITIAL_LAYER_LIST_SIZE = 500;

  private:
    //aggregate
    sf::RenderWindow*         m_window; 
    //composite
    std::vector<Renderable*>* m_layers[MAX_LAYERS];
    unsigned int              m_layerVacantIdx[MAX_LAYERS];
    //cameras
    Camera                    m_cameras[MAX_CAMERAS];
    sf::RenderTexture         m_renderTextures[MAX_CAMERAS];

  public:
    Renderer(sf::RenderWindow* window);
    ~Renderer();

    /*
     * Get a list of renderables and sort them into the layers
     */
    void PushRenderables(const std::vector<Renderable*>& renderables);
    /*
     * push cameras 
     */
    void PushCameras(Camera cameras[MAX_CAMERAS]);
    /*
     * Draw everything in m_layers in order from 0 to 31 
     * (higher numbers are drawn on top) from the cameras' perspectives
     */
    void Draw();
    /*
     * remove all renderables from the layers
     */
    void ClearRenderables();
    /*
     * remove all cameras
     */
    void ClearCameras();

  };
}
