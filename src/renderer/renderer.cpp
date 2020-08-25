#include "poppingamer/renderer/renderer.hpp" 

#include <iostream>

/*
 * CURRENTLY A BUG WHEN INCREASING CAPACITY OF LAYERS. A COUPLE ELEMENTS
 * WILL JUST NOT BE DRAWN FOR SOME REASON IDK MAN.
 */
namespace pg {

  /*
   * CONSTRUCTOR
   */
  Renderer::Renderer(sf::RenderWindow* window) {
    m_window = window;
    for (int i = 0; i < MAX_LAYERS; i++) {
      m_layers[i] = new std::vector<Renderable*>(INITIAL_LAYER_LIST_SIZE, NULL);
    }
    for (int i = 0; i < MAX_LAYERS; i++) {
      m_layerVacantIdx[i] = 0;
    }
  }

  Renderer::~Renderer() {
    for (int i = 0; i < MAX_LAYERS; i++) {
      delete m_layers[i];
    }
  }

  void Renderer::PushCameras(Camera cameras[MAX_CAMERAS]) {
    for (int i = 0; i < MAX_CAMERAS; i++) {
      m_cameras[i] = cameras[i];
    }
  }
  
  void Renderer::PushRenderables(const std::vector<Renderable*>& renderables) {
    for (int i = 0; i < renderables.size(); i++) {
      if (renderables[i] == NULL) { continue; }
      //get layer
      unsigned int layer = renderables[i]->GetLayer();
      if (layer >= MAX_LAYERS) { continue; }
      //add to layer
      unsigned int vacantIdx = m_layerVacantIdx[layer];
      std::vector<Renderable*>* renderListLayer = m_layers[layer];
      //add to layer renderable list
      //if layer is at capactiy, pushback to resize
      if (vacantIdx > renderListLayer->size()) {
        renderListLayer->push_back(renderables[i]);
      }
      //if default size hasn't been exceeded, insert by idx
      else {
        (*renderListLayer)[vacantIdx] = renderables[i];
      }
      vacantIdx++;
      m_layerVacantIdx[layer] = vacantIdx;
    }
  }

  /*
   * Draw the whole scene onto rt
   */
  void Renderer::Draw() {
    m_window->clear(sf::Color(0,0,0,255));
    //FOR EACH CAMERA
    int object = 0;
    for (int c = 0; c < MAX_CAMERAS; c++) {
      //skip camera if it doesn't have a framebuffer to draw to
      if (m_cameras[c].m_rTexture == NULL) { continue; }
      Camera camera = m_cameras[c];
      camera.m_rTexture->clear(sf::Color(0,0,0,0)); //clear a transparent color
      //FOR EACH LAYER
      for (int l = 0; l < MAX_LAYERS; l++) {
        std::vector<Renderable*>* layer = m_layers[l];
        unsigned int layerVacantIdx = m_layerVacantIdx[l];
        //FOR EACH RENDERABLE
        for (int r = 0; r < layerVacantIdx; r++) {
          Renderable* renderable = (*layer)[r];
          //if renderable is null, don't render
          if (renderable == NULL) {
            continue;
          }
          //if renderable is not within the layer range,  don't render
          if (renderable->GetLayer() >= MAX_LAYERS) {
            continue;
          }
          renderable->Draw(camera);
        }//end renderable
      }//end layer
      camera.BindView();
      camera.m_rTexture->display();
      sf::Sprite framebuffer(camera.m_rTexture->getTexture());
      unsigned int scale = camera.m_scale;
      framebuffer.setScale(scale, scale);
      m_window->draw(framebuffer);
    }//end camera
    ClearRenderables();
    m_window->display();
  }

  void Renderer::ClearRenderables() {
    for (int i = 0; i < MAX_LAYERS; i++) {
      std::vector<Renderable*>* layer = m_layers[i];
      m_layerVacantIdx[i] = 0;
      for (int j = 0; j < layer->size(); j++) {
        (*layer)[j] = NULL;
      }
    }
  }
}
