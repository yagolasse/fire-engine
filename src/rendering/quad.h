#pragma once

#include <glm.hpp>

struct Transform {
    glm::vec2 scale;
    glm::vec2 position;
    float rotationDegrees;
};

struct Quad {
    Transform transform;
    glm::vec4 color;
};

struct QuadVertex {
    glm::mat4 transform;
    glm::vec4 color;
};
