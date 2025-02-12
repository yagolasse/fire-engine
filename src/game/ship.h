#pragma once

#include "sprite.h"

struct InputEvent;

class Ship : public Sprite {
   private:
    const float speed = 180.0f;
    const float rotationSpeed = 50.0f;

   public:
    using Sprite::Sprite;

    void start() override;
    void update(double delta) override;
    bool onKeyEvent(Input::Key key, Input::KeyEventType type) override;
};
