#pragma once

#include <string>

#include <glm/glm.hpp>

#include <graphic.hpp>
#include <renderer.hpp>

class ASCIIGraphic : public Graphic {
public:
  ASCIIGraphic(char character, std::string texturePath, glm::vec2 position, glm::vec2 size, bool transparent);
  void render(Renderer* renderer);

private:
  int character_; // the integer representation of the ascii character
};
