#include <text.hpp>

#include <config.hpp>

Text::Text(std::string text, glm::vec2 position, glm::vec2 letter_size, glm::vec2 spacing) {
  letter_size_ = letter_size;
  scale_ = Config::getScale();

  int c = 0;
  for (auto ch : text) {
    glm::vec2 pos = {position.x + letter_size.x * c, position.y};
    letter = new ASCIIGraphic(ch, "assets/ascii.gif", pos, letter_size, true);
    letters_.push_back(letter);
    c++;
  }
}

void Text::render(Renderer* renderer) {
  for (auto& letter : letters_) {
    letter->render(renderer);
  }
}

void Text::setPosition(glm::vec2 position) {
  int c = 0;
  for (auto& letter : letters_) {
    glm::vec2 pos = {position.x + letter_size_.x * c, position.y};
    letter->setPosition(pos);
    c++;
  }
}

void Text::update(double dt) {
  for (auto& letter : letters_) {
    letter->update(dt);
  }
  scale();
}

void Text::scale() {
  glm::vec2 scale = Config::getScale();
  if (scale_ != scale) {
    scale_ = scale;
    letter_size_ *= scale;
  }
}
