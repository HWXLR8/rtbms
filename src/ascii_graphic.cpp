#include <ascii_graphic.hpp>

ASCIIGraphic::ASCIIGraphic(char character, std::string texturePath, glm::vec2 position, glm::vec2 size, bool transparent) : Graphic(texturePath, position, size, transparent) {
  character_ = static_cast<int>(character);
}

void ASCIIGraphic::render(Renderer* renderer) {
  float verts[24] = {
    // pos      // tex
    0.0f, 1.0f, character_ * (1.0f/128.0f), 1.0f,
    1.0f, 0.0f, character_ * (1.0f/128.0f) + (1.0f/128.0f), 0.0f,
    0.0f, 0.0f, character_ * (1.0f/128.0f), 0.0f,
    0.0f, 1.0f, character_ * (1.0f/128.0f), 1.0f,
    1.0f, 1.0f, character_ * (1.0f/128.0f) + (1.0f/128.0f), 1.0f,
    1.0f, 0.0f, character_ * (1.0f/128.0f) + (1.0f/128.0f), 0.0f
  };

  renderer->setBufferData(verts);
  Graphic::render(renderer);
  renderer->setDefaultBufferData();
}
