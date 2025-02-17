#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <glm.hpp>
#include <memory>

#include "game_object.hpp"

class TextureData;
class TextureRegion;
class Quad;

class Sprite : public GameObject {
   protected:
    int spriteWidth;
    int spriteHeight;
    glm::vec4 tint;
    TextureData* textureData;
    TextureRegion* textureRegion;

    Quad mapToQuad();

   public:
    int currentSprite;

    Sprite();
    virtual ~Sprite();
    virtual void start() override;
    virtual void update(double delta) override;
};

#endif
