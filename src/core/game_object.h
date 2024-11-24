#pragma once

#include "quad.h"

class GameObject {
   public:
    Transform transform;

    virtual ~GameObject() = default;

    virtual void start() { }
    virtual void update(double delta) { }

   protected:
    GameObject() {
        transform = Transform{
            glm::vec2{1.0f, 1.0f},
            glm::vec2{0.0f, 0.0f},
            0.0f,
        };
    }
};