#pragma once

#include "batch_renderer.h"
#include "game_object.h"
#include "texture_data.h"
#include "texture_region.h"

class Sprite : public GameObject {
   private:
    int spriteWidth;
    int spriteHeight;
    TextureData textureData;
    TextureRegion textureRegion;
    std::shared_ptr<BatchRenderer> batchRenderer;

    Quad mapToQuad();

   public:
    int currentSprite;

    Sprite(std::shared_ptr<BatchRenderer> batchRenderer, TextureData textureData, int spriteWidth, int spriteHeight);
    void update(double delta) override;
};
