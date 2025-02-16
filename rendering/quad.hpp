#ifndef QUAD_HPP
#define QUAD_HPP

#include <array>
#include <glm.hpp>

struct Transform {
    glm::vec2 scale = glm::vec2{1.0f, 1.0f};
    glm::vec2 position = glm::vec2{0.0f, 0.0f};
    float rotationDegrees = 0.0f;
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

#endif
