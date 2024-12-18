#pragma once

#include <array>
#include <glm.hpp>

struct Transform {
    glm::vec2 scale;
    glm::vec2 position;
    float rotationDegrees;
};

struct Quad {
    Transform transform;
    glm::vec4 color;
    std::array<glm::vec2, 4> uv;
    std::uint8_t textureIndex;
};

struct QuadVertex {
    glm::vec2 position;
    glm::i8vec4 color;
    glm::vec2 uv;
    std::uint8_t textureIndex;
};
