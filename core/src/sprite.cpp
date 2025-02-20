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

Sprite::Sprite() : GameObject(), currentSprite(0), tint(glm::vec4(1.0f)) {
}

Sprite::~Sprite() {
    delete textureRegion;
    // Texture data should not be deleted here because it is managed somewhere else
}

void Sprite::start() {
}

void Sprite::update(double delta) {
}

void Sprite::setTexture(const char* resource) {
    textureData = TextureStorage::getInstance()->loadTexture(resource);
}

void Sprite::render() {
    BatchRenderer::getInstance()->pushQuad(mapToQuad());
}

void Sprite::setTileSize(int width, int height) {
    if(textureRegion) {
        delete textureRegion;
    }
    textureRegion = new TextureRegion(textureData, 64, 64);
}

Quad Sprite::mapToQuad() {
    glm::vec2 scale = glm::vec2{textureRegion->getSpriteWidth(), textureRegion->getSpriteHeight()} * transform->scale;
    Transform quadTrasnform = {scale, transform->position, transform->rotationDegrees};

    return Quad{quadTrasnform, tint, textureRegion->getUVMappingForRegion(currentSprite), (unsigned char)textureData->index};
}
