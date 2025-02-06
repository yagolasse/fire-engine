#include "texture_region.h"

#include "texture_data.h"

TextureRegion::TextureRegion(TextureData* textureData, int spriteWidth, int spriteHeight)
    : textureData(textureData), spriteWidth(spriteWidth), spriteHeight(spriteHeight) {
}

std::array<glm::vec2, 4> TextureRegion::getUVMappingForRegion(int frameIndex) {
    float spriteWidthPercent = (float)spriteWidth / textureData->width;
    float spriteHeightPercent = (float)spriteHeight / textureData->height;

    spriteWidthPercent *= textureData->maxUV.x;
    spriteHeightPercent *= textureData->maxUV.y;

    int spritesPerRow = textureData->width / spriteWidth;

    float spriteX = (frameIndex % spritesPerRow) * spriteWidthPercent;
    float spriteY = (frameIndex / spritesPerRow) * spriteHeightPercent;

    return std::array<glm::vec2, 4>{
        glm::vec2{spriteX, spriteY},
        glm::vec2{spriteX + spriteWidthPercent, spriteY},
        glm::vec2{spriteX + spriteWidthPercent, spriteY + spriteHeightPercent},
        glm::vec2{spriteX, spriteY + spriteHeightPercent},
    };
}
