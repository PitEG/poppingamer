#include "poppingamer/renderer/renderer.hpp" 

#include <iostream>


namespace pg {
  /*
   * CONSTRUCTOR
   */
  Renderer::Renderer(sf::RenderWindow* window) {
    m_window = window;
  }

  Renderer::~Renderer() {
  }

  void Renderer::PushCameras(Camera cameras[MAX_CAMERAS], 
      sf::RenderTexture* rt[MAX_CAMERAS]) {

    for (int i = 0; i < MAX_CAMERAS; i++) {
      m_cameras[i] = cameras[i];
    }
    for (int i = 0; i < MAX_CAMERAS; i++) {
      m_renderTextures[i] = rt[i];
    }
  }
  
  void Renderer::PushRenderables(const std::vector<Renderable*>& renderables) {
    for (int i = 0; i < renderables.size(); i++) {
      //get layer
      unsigned int layer = renderables[i]->GetLayer();
      if (layer >= MAX_LAYERS) { continue; } //skip if out of bounds
      //add to layer renderable list
      std::vector<Renderable*>& renderListLayer = m_layers[layer];
      unsigned int layerVacantIdx = m_layerVacantIdx[layer];
      if (renderListLayer.size() <= layerVacantIdx) {
        renderListLayer.push_back(renderables[i]);
      }
      else {
        renderListLayer[layerVacantIdx] = renderables[i];
      }
      //update vacant idx
      m_layerVacantIdx[layer] += 1;
    }
  }

  /*
   * Draw the whole scene onto rt
   */
  void Renderer::Draw() {
    m_window->clear(sf::Color(0,0,0,255));
    //FOR EACH CAMERA
    for (int c = 0; c < MAX_CAMERAS; c++) {
      //skip camera if it doesn't have a framebuffer to draw to
      Camera camera = m_cameras[c];
      //skip if disabled
      if (camera.enabled == false) { continue; }
      sf::RenderTexture* rt = m_renderTextures[c];
      m_renderTextures[c]->clear(sf::Color(0,0,0,0)); //clear a transparent color
      //FOR EACH LAYER
      for (int l = 0; l < MAX_LAYERS; l++) {
        std::vector<Renderable*>& layer = m_layers[l];
        //FOR EACH RENDERABLE
        for (int r = 0; r < layer.size(); r++) {
          Renderable* renderable = layer[r];
          //if renderable is null, don't render
          if (renderable->m_shouldRender == false) { continue; }
          //if renderable is not within the layer range,  don't render
          if (renderable->GetLayer() >= MAX_LAYERS) {
            continue;
          }
          renderable->Draw(camera, rt);
        }//end renderable
      }//end layer
      rt->display(); //draw onto rendertexture
      sf::Sprite framebuffer(rt->getTexture());
      m_window->draw(framebuffer); //draw onto window
    }//end camera
    ClearRenderables();
    m_window->display();
  }

  void Renderer::ClearRenderables() {
    //for each layer
    for (int i = 0; i < MAX_LAYERS; i++) {
      std::vector<Renderable*> layer = m_layers[i];
      m_layerVacantIdx[i] = 0;
      //for each element
      for (int j = 0; j < layer.size(); j++) {
        layer[i] = NULL;
      }
    }
  }
}
