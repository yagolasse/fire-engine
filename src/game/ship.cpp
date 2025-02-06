#include "ship.h"

#include "quad.h"

void Ship::start() {
}

void Ship::update(double delta) {
    transform->position.x += 30 * delta;
    transform->position.y += 30 * delta;

    Sprite::update(delta);
}
