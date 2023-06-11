#include <note.hpp>

Note::Note(std::string texturePath, glm::vec2 position, glm::vec2 size, bool transparent):
  Graphic(texturePath, position, size, transparent) {
  init();
  active_ = false;
}


void Note::update(double dt) {
  position_ += glm::vec2{0, speed_.y * dt};
}

void Note::activate() {
  active_ = true;
}

void Note::deactivate() {
  active_ = false;
}

bool Note::isActive() {
  return active_;
}

void Note::init() {
  int offset = rand() % 7;

  speed_ = {0, 1000};
  position_ = {54 * offset, 0};
}
