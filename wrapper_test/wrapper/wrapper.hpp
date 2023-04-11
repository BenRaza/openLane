#pragma once

#include <vector>
#include "../vertex3D/vertex3D.hpp"
#include "glimac/default_shader.hpp"
#include "p6/p6.h"

struct Wrapper {
    const GLuint          VERTEX_ATTR_POSITION = 0;
    const GLuint          VERTEX_ATTR_COLOR    = 1;
    GLuint                vbo                  = 0;
    GLuint                vao                  = 0;
    GLuint                ibo                  = 0;
    std::vector<Vertex3D> vertices;
    std::vector<uint32_t> indices;
    void                  init();
    void                  draw();
    void                  finish();
};