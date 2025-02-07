#pragma once

#include "sprite.h"

class Ship : public Sprite {
   private:
    const float speed = 100.0f;

   public:
    using Sprite::Sprite;

    void start() override;
    void update(double delta) override;
};
