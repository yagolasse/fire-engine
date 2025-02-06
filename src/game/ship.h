#pragma once

#include "sprite.h"

class Ship : public Sprite {
    using Sprite::Sprite;
    
    void start() override;
    void update(double delta) override;
};
