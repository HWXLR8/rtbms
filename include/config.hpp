#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

class Config {
public:
  static glm::vec2 SCALE;
  static glm::vec2 SCREEN_SIZE;

  static void calculateNewScale(glm::vec2 new_screen_size);
  static glm::vec2 getScale();
};
