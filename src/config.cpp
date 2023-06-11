#include <config.hpp>

glm::vec2 Config::SCALE = {1.0, 1.0};
glm::vec2 Config::SCREEN_SIZE = {640, 480};

void Config::calculateNewScale(glm::vec2 new_screen_size) {
  SCREEN_SIZE = new_screen_size;
}

glm::vec2 Config::getScale() {
  return SCALE;
}
