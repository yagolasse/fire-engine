#pragma once

#include "sprite.h"

class Star : public Sprite {
   public:
    using Sprite::Sprite;
    
    void start() override;
    void update(double delta) override;
};
