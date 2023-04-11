#pragma once

#include "p6/p6.h"

struct Vertex3D {
    glm::vec3 m_position{};
    glm::vec3 m_color{};

    Vertex3D(glm::vec3 position, glm::vec3 color)
        : m_position(position), m_color(color){};
};