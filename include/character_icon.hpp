#pragma once

#include <graphic.hpp>

class CharacterIcon {
public:
  CharacterIcon(std::string character_name, glm::vec2 position);
  void render(Renderer* renderer);
  void toggleDrag();
  bool isActive(glm::vec2 mouse_pos);
  void update(glm::vec2 mouse_pos, double dt);
  std::string getCharacterName();
  bool isBeingDragged();
  void setPosition(glm::vec2 new_position);
  glm::vec2 getPosition();

private:
  Graphic* icon_;
  glm::vec2 position_;
  glm::vec2 size_;
  bool drag_ = false;
  std::string character_name_;
};
