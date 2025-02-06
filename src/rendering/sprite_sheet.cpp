#include "sprite_sheet.h"

#include <iostream>

#include "texture.h"

SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture, int spriteWidth, int spriteHeight)
    : texture(texture), spriteWidth(spriteWidth), spriteHeight(spriteHeight) {
    textureWidth = texture->getWidth();
    textureHeight = texture->getHeight();
}

std::array<glm::vec2, 4> SpriteSheet::getUVMappingForRegion(int frameIndex) {
    float spriteWidthPercent = (float)spriteWidth / textureWidth;
    float spriteHeightPercent = (float)spriteHeight / textureHeight;

    int spritesPerRow = textureWidth / spriteWidth;

    float spriteX = (frameIndex % spritesPerRow) * spriteWidthPercent;
    float spriteY = (frameIndex / spritesPerRow) * spriteHeightPercent;

    return std::array<glm::vec2, 4>{
        glm::vec2{spriteX, spriteY},
        glm::vec2{spriteX + spriteWidthPercent, spriteY},
        glm::vec2{spriteX + spriteWidthPercent, spriteY + spriteHeightPercent},
        glm::vec2{spriteX, spriteY + spriteHeightPercent},
    };
}

inline void SpriteSheet::bindTexture() const {
    texture->bind();
}
