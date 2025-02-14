#ifndef SHIP_HPP
#define SHIP_HPP

#include "sprite.hpp"

struct InputEvent;

class Ship : public Sprite {
   private:
    const float speed = 180.0f;
    const float rotationSpeed = 50.0f;
    const float shootTimeout = 0.5f;

    float shootTime = 0.0f;

   public:
    Ship();

    void start() override;
    void update(double delta) override;
    bool onKeyEvent(Input::Key key, Input::KeyEventType type) override;
};

#endif
