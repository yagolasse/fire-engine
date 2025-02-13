#ifndef TEXTURE_REGION_HPP
#define TEXTURE_REGION_HPP

#include <array>
#include <glm.hpp>

class TextureData;

class TextureRegion {
   private:
    TextureData* textureData;

    int spriteWidth;
    int spriteHeight;

   public:
    TextureRegion(TextureData* textureData, int spriteWidth, int spriteHeight);
    std::array<glm::vec2, 4> getUVMappingForRegion(int frameIndex);

    inline int getSpriteWidth() const {
        return spriteWidth;
    }

    inline int getSpriteHeight() const {
        return spriteHeight;
    }
};

#endif
