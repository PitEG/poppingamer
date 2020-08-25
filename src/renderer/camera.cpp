#include "poppingamer/renderer/camera.hpp" 

namespace pg {
  Camera::Camera(Entity* entity, sf::View view, sf::RenderTexture* rt, unsigned int scale)
  : Component(entity), m_view(view), m_rTexture(rt), m_scale(scale) {
  }

  void Camera::BindView() {
    m_rTexture->setView(m_view);
  }
}
