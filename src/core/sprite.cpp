#include "sprite.hpp"

#include <glm.hpp>
#include <iostream>
#include <string>

#include "batch_renderer.hpp"
#include "game_object.hpp"
#include "input.hpp"
#include "quad.hpp"
#include "texture_data.hpp"
#include "texture_region.hpp"
#include "texture_storage.hpp"

Sprite::Sprite(std::shared_ptr<BatchRenderer> batchRenderer, TextureData* textureData, int spriteWidth, int spriteHeight)
    : currentSprite(0),
      tint(glm::vec4(1.0f)),
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
    batchRenderer->pushQuad(mapToQuad());
}

Quad Sprite::mapToQuad() {
    glm::vec2 scale = glm::vec2{textureRegion->getSpriteWidth(), textureRegion->getSpriteHeight()} * transform->scale;
    Transform quadTrasnform = {scale, transform->position, transform->rotationDegrees};

    return Quad{quadTrasnform, tint, textureRegion->getUVMappingForRegion(currentSprite), (unsigned char)textureData->index};
}
