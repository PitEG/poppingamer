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
  
  void Renderer::PushRenderables(const std::vector<Renderable>& renderables) {
    for (int i = 0; i < renderables.size(); i++) {
      //get layer
      unsigned int layer = renderables[i].GetLayer();
      if (layer >= MAX_LAYERS) { continue; } //skip if out of bounds
      //add to layer
      std::vector<Renderable>& renderListLayer = m_layers[layer];
      //add to layer renderable list
      renderListLayer.push_back(renderables[i]);
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
      sf::RenderTexture* rt = m_renderTextures[c];
      m_renderTextures[c]->clear(sf::Color(0,0,0,0)); //clear a transparent color
      //FOR EACH LAYER
      for (int l = 0; l < MAX_LAYERS; l++) {
        std::vector<Renderable>& layer = m_layers[l];
        //FOR EACH RENDERABLE
        for (int r = 0; r < layer.size(); r++) {
          Renderable& renderable = layer[r];
          //if renderable is null, don't render
          if (renderable.m_shouldRender == false) { continue; }
          //if renderable is not within the layer range,  don't render
          if (renderable.GetLayer() >= MAX_LAYERS) {
            continue;
          }
          renderable.Draw(camera, rt);
        }//end renderable
      }//end layer
      //draw onto rendertexture
      rt->display();
      //draw onto window
      sf::Sprite framebuffer(rt->getTexture());
      unsigned int scale = 1; //TODO temporary
      framebuffer.setScale(scale, scale);
      m_window->draw(framebuffer);
    }//end camera
    ClearRenderables();
    m_window->display();
  }

  void Renderer::ClearRenderables() {
    //for each layer
    for (int i = 0; i < MAX_LAYERS; i++) {
      std::vector<Renderable>& layer = m_layers[i];
      //for each element
      for (int j = 0; j < layer.size(); j++) {
        layer[i].m_shouldRender == false;
      }
    }
  }
}
