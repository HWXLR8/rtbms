#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum MouseAction {
  LEFT_CLICK,
  RIGHT_CLICK,
  MIDDLE_CLICK,
  SCROLL_UP,
  SCROLL_DOWN,
  NONE,
};

class Input {
public:
  Input(GLFWwindow* window);
  glm::vec2 getMousePosition();
  void process(double dt);

private:
  bool click_ = false;
  bool keys_[1024] = {false};
  glm::vec2 mouse_pos_;
  MouseAction mouse_action_;

  void runMouseCommand();

  // callbacks
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
  void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
  void framebufferSizeCallback(GLFWwindow* window, int width, int height);
  void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
  void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};
