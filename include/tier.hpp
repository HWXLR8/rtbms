#pragma once

#include <optional>
#include <string>
#include <vector>

#include <character_icon.hpp>
#include <text.hpp>

class Tier {
public:
  Tier(int num, std::string name, glm::vec2 position, glm::vec2 size, std::optional<std::vector<std::string>> characters);
  void createNewIcon(std::string character_name);
  void addExistingIcon(CharacterIcon* icon);
  void removeIcon(CharacterIcon* icon);
  void render(Renderer* renderer);
  void update(glm::vec2 mouse_pos, bool part_icons, double dt);
  CharacterIcon* getActiveIcon(glm::vec2 mouse_pos);
  bool isActive(glm::vec2 mouse_pos);
  void clean(bool part_icons); // move icons to their correct positions
  void getActiveIndex(glm::vec2 mouse_pos);
  glm::vec2 getSize();
  glm::vec2 getPosition();
  void setPosition(glm::vec2 position);
  int getTierNumber();
  void scrollDown();
  void scrollUp();

private:
  int num_;
  std::string name_;
  glm::vec2 position_;
  glm::vec2 size_;
  glm::vec2 scale_;
  Graphic* bg_;
  std::vector<CharacterIcon*> icons_;
  glm::vec2 icon_capacity_;
  glm::vec2 last_icon_index_ = {-1, -1};
  std::optional<glm::vec2> active_index_;
  Text* label_;

  glm::vec2 getLastIconPosition();
  void incrementIconIndex();
  void decrementIconIndex();
  void scale();
};
