#include "sprite.h"

#include <glm.hpp>
#include <iostream>
#include <string>

#include "texture_storage.h"

Sprite::Sprite(std::shared_ptr<BatchRenderer> batchRenderer, TextureData textureData, int spriteWidth, int spriteHeight)
    : GameObject(),
      currentSprite(0),
      textureData(textureData),
      batchRenderer(batchRenderer),
      textureRegion(textureData, spriteWidth, spriteHeight) {
}

void Sprite::update(double delta) {
    transform.position.x += 30 * delta;
    transform.position.y += 30 * delta;

    batchRenderer->pushQuad(mapToQuad());
}

Quad Sprite::mapToQuad() {
    return Quad{
        {glm::vec2{textureRegion.getSpriteWidth(), textureRegion.getSpriteHeight()} * transform.scale,
         transform.position, glm::radians(transform.rotationDegrees)},
        glm::vec4(1.0f),
        textureRegion.getUVMappingForRegion(currentSprite),
        (unsigned char)textureData.index,
    };
}
