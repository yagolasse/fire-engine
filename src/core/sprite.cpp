#include "sprite.h"

#include <glm.hpp>
#include <iostream>
#include <string>

#include "batch_renderer.h"
#include "game_object.h"
#include "quad.h"
#include "texture_data.h"
#include "texture_region.h"
#include "texture_storage.h"

Sprite::Sprite(std::shared_ptr<BatchRenderer> batchRenderer, TextureData* textureData, int spriteWidth, int spriteHeight)
    : currentSprite(47),
      textureData(textureData),
      batchRenderer(batchRenderer),
      textureRegion(new TextureRegion(textureData, spriteWidth, spriteHeight)) {
}

Sprite::~Sprite() {
    delete textureRegion;
    // Texture data should not be deleted here because it is managed somewhere else
}

void Sprite::start() {
    
}

void Sprite::update(double delta) {
    transform->position.x += 30 * delta;
    transform->position.y += 30 * delta;

    batchRenderer->pushQuad(mapToQuad());
}

Quad Sprite::mapToQuad() {
    return Quad{
        {glm::vec2{textureRegion->getSpriteWidth(), textureRegion->getSpriteHeight()} * transform->scale,
         transform->position, glm::radians(transform->rotationDegrees)},
        glm::vec4(1.0f),
        textureRegion->getUVMappingForRegion(currentSprite),
        (unsigned char)textureData->index,
    };
}
