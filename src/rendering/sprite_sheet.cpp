#include "sprite_sheet.h"

#include <iostream>

SpriteSheet::SpriteSheet(std::shared_ptr<Texture> texture, int spriteWidth, int spriteHeight)
    : texture(texture), spriteWidth(spriteWidth), spriteHeight(spriteHeight) {
    textureWidth = texture->getWidth();
    textureHeight = texture->getHeight();
}

std::array<glm::vec2, 4> SpriteSheet::getUVMappingForRegion(int frameIndex) {
    const float tw = float(spriteWidth) / textureWidth;
    const float th = float(spriteHeight) / textureHeight;
    const int numPerRow = textureWidth / spriteWidth;
    const float tx = (frameIndex % numPerRow) * tw;
    const float ty = (frameIndex / numPerRow + 1) * th;
    
    std::cout << tx << ":" << ty << std::endl;

    return std::array<glm::vec2, 4>{
        glm::vec2{tx, ty},
        glm::vec2{tx + tw, ty},
        glm::vec2{tx + tw, ty + th},
        glm::vec2{tx, ty + th},
    };
}
