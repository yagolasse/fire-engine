#ifndef TRANSFORM_3D_HPP
#define TRANSFORM_3D_HPP

#include <glm.hpp>

struct Transform3D {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
};

#endif
