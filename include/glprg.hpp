#pragma once

#include <GLFW/glfw3.h>

#include <optional>

#include <graphic.hpp>
#include <input.hpp>
#include <note.hpp>
#include <text.hpp>
#include <tier.hpp>

class GLPRG {
 public:
  GLPRG();
  ~GLPRG();
  void run();

private:
  GLFWwindow* window_;
  Input* input_;
  glm::vec2 mouse_pos_;
  std::vector<Note*> notes_;

  void initGLFW();
  void initGLAD();
  void initGL();
  void update(double dt);
  void render();
  void framebufferSizeCallback(GLFWwindow* window, int width, int height);
  void windowSizeCallback(GLFWwindow* window, int width, int height);
  void recalculateProjectionMatrix(glm::vec2 new_screen_size);

  void deleteOffScreenNotes();
  void spawnNote();
  void initNotePool(int n);
};
