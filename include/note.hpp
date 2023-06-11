#pragma once

#include <graphic.hpp>

#include <glm/gtc/type_ptr.hpp>

class Note : public Graphic {
public:
  Note(std::string texturePath, glm::vec2 position, glm::vec2 size, bool transparent);
  void update(double dt) override;
  void activate();
  void deactivate();
  bool isActive();
  void init();

private:
  glm::vec2 speed_;
  bool active_;
};
