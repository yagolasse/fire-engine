#pragma once

#include <memory>

#include "game_object.h"

class BatchRenderer;
class TextureData;
class TextureStorage;
class TextureRegion;
class Quad;

class Sprite : public GameObject {
   private:
    int spriteWidth;
    int spriteHeight;
    TextureData& textureData;
    TextureRegion* textureRegion;
    std::shared_ptr<BatchRenderer> batchRenderer;

    Quad mapToQuad();

   public:
    int currentSprite;

    Sprite(std::shared_ptr<BatchRenderer> batchRenderer, TextureData& textureData, int spriteWidth, int spriteHeight);
    ~Sprite();
    void start() override;
    void update(double delta) override;
};
