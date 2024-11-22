#pragma once

#include <glm.hpp>

#include "quad.h"
#include "texture.h"

class Sprite {
   private:
    Quad quad;

   public:
    Sprite(glm::vec2 position, glm::vec2 scale, Texture texture);

    inline Quad getQuad() const {
        return quad;
    }
};
