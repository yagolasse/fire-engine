#pragma once

#include "sprite.h"

class Star : public Sprite {
   private:
    const float baseSpeed = 100;
    float speed;

   public:
    using Sprite::Sprite;

    void start() override;
    void update(double delta) override;
};
