#include "poppingamer/renderer/camera.hpp" 

namespace pg {
  Camera::Camera(sf::View view, sf::RenderTexture* rt, unsigned int scale)
  : Component(-1), m_view(view), m_rTexture(rt), m_scale(scale) {
  }

  void Camera::BindView() {
    m_rTexture->setView(m_view);
  }
}
