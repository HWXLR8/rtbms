#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>
#include <thread>
#include <vector>

#include <glprg.hpp>
#include <resource_manager.hpp>
#include <renderer.hpp>
#include <config.hpp>

Renderer *renderer;

GLPRG::GLPRG() {
  // window/GL
  initGLFW();
  initGLAD();
  initGL();

  // hack GLFW to accept a c++ member function as a callback
  auto framebufferSizeCallbackAlias = [](GLFWwindow* window, int width, int height) {
    static_cast<GLPRG*>(glfwGetWindowUserPointer(window))->framebufferSizeCallback(window, width, height);
  };
  auto windowSizeCallbackAlias = [](GLFWwindow* window, int width, int height) {
    static_cast<GLPRG*>(glfwGetWindowUserPointer(window))->windowSizeCallback(window, width, height);
  };
  glfwSetFramebufferSizeCallback(window_, framebufferSizeCallbackAlias);
  glfwSetWindowSizeCallback(window_, windowSizeCallbackAlias);

  // main shader
  ResourceManager::loadShader("shader/vert.glsl", "shader/frag.glsl", nullptr, "static_image");
  glm::mat4 projection = glm::ortho(0.0f, Config::SCREEN_SIZE.x, Config::SCREEN_SIZE.y, 0.0f, -100.0f, 100.0f);
  ResourceManager::getShader("static_image").use().setInteger("image", 0);
  ResourceManager::getShader("static_image").setMatrix4("projection", projection);
  Shader shader = ResourceManager::getShader("static_image");
  renderer = new Renderer(shader);

  // input
  input_ = new Input(window_);

  initNotePool(50);
  spawnNote();
}

GLPRG::~GLPRG() {
  ResourceManager::clear();
  glfwTerminate();
}

void GLPRG::initGLFW() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif
  glfwWindowHint(GLFW_RESIZABLE, false);
  window_ = glfwCreateWindow(Config::SCREEN_SIZE.x, Config::SCREEN_SIZE.y, "WINDOW TITLE", nullptr, nullptr);
  glfwMakeContextCurrent(window_);
}

void GLPRG::initGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
    return;
  }
}

void GLPRG::initGL() {
  glViewport(0, 0, Config::SCREEN_SIZE.x, Config::SCREEN_SIZE.y);
  // glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLPRG::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  glm::vec2 new_screen_size {width, height};
  recalculateProjectionMatrix(new_screen_size);
}

void GLPRG::windowSizeCallback(GLFWwindow* window, int width, int height) {
  glm::vec2 new_screen_size {width, height};
  Config::calculateNewScale(new_screen_size);
  // recalculateProjectionMatrix(new_screen_size);
}

void GLPRG::recalculateProjectionMatrix(glm::vec2 new_screen_size) {
  glm::mat4 projection = glm::ortho(0.0f, new_screen_size.x, new_screen_size.y, 0.0f, -100.0f, 100.0f);
  ResourceManager::getShader("static_image").setMatrix4("projection", projection);
}

void GLPRG::update(double dt) {
  mouse_pos_ = input_->getMousePosition();
  input_->process(dt);

  for (auto note : notes_) {
    note->update(dt);
  }

  if (rand() % 1000 == 1) {
    spawnNote();
  }
  deleteOffScreenNotes();
}

void GLPRG::render() {
  Shader static_image = ResourceManager::getShader("static_image");
  renderer->setShader(static_image);

  for (auto note : notes_) {
    if (note->isActive()) {
      note->render(renderer);
    }
  }
}

void GLPRG::run() {
  double dt = 0.0;
  double lastFrame = glfwGetTime();
  while (!glfwWindowShouldClose(window_)) {
    double currentFrame = glfwGetTime();
    dt = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    update(dt);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    render();
    glfwSwapBuffers(window_);
  }
}

void GLPRG::deleteOffScreenNotes() {
  for (auto note : notes_) {
    if (note->getPosition().y > Config::SCREEN_SIZE.y) {
      note->deactivate();
    }
  }
}

void GLPRG::spawnNote() {
  for (auto note : notes_) {
    if (!note->isActive()) {
      note->init();
      note->activate();
      return;
    }
  }
}

void GLPRG::initNotePool(int n) {
  for (int i = 0; i < n; ++i) {
    Note* note = new Note("assets/note.png", glm::vec2(0, 0), glm::vec2(54, 18), true);
    notes_.push_back(note);
  }
}
