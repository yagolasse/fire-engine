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
    glm::vec2 position;
    glm::i8vec4 color;
    glm::vec2 uv;
};
