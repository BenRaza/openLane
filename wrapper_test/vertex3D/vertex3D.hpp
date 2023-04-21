#pragma once

#include "p6/p6.h"

struct Vertex3D {
    glm::vec3 _position{};
    glm::vec3 _color{};

    Vertex3D(glm::vec3 position, glm::vec3 color)
        : _position(position), _color(color){};
};