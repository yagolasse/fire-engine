#pragma once

#include <array>
#include <memory>
#include <glm.hpp>

#include "texture.h"

class SpriteSheet {
   private:
    std::shared_ptr<Texture> texture;

    int spriteWidth;
    int spriteHeight;
    int textureWidth;
    int textureHeight;

   public:
    SpriteSheet(std::shared_ptr<Texture> texture, int spriteWidth, int spriteHeight);

    std::array<glm::vec2, 4> getUVMappingForRegion(int frameIndex);

    inline int getSpriteWidth() const {
        return spriteWidth;
    }

    inline int getSpriteHeight() const {
        return spriteHeight;
    }

    // TODO: Remove later
    inline void bindTexture() const {
        texture->bind();
    }
};
