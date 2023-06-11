#pragma once

#include <glm/glm.hpp>

#include <texture.hpp>
#include <shader.hpp>

class Renderer {
 public:
  Renderer(Shader& shader);
  ~Renderer();

  void setShader(Shader& shader);
  void blit(Texture2D &texture, glm::vec2 position, glm::vec2 size, glm::vec3 rotation, glm::vec4 color);
  void setBufferData(float (&verts)[24]);
  void setDefaultBufferData();

 private:
  Shader shader_;
  unsigned int quadVAO_;
  unsigned int VBO_;

  float default_verts_[24] = {
    // pos      // tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  void initRenderData();
};
