#include "star.h"

#include <iostream>

#include "assertion.h"
#include "random.h"
#include "quad.h"
#include "window.h"

void Star::start() {
    currentSprite = 21;

    transform->position.x = Window::getWidth() * Random::getFloat();
    transform->position.y = Window::getHeight() * Random::getFloat();

    transform->scale *= 0.3f * Random::getFloat() + 0.05f;

    speed = transform->scale.x * baseSpeed;

    Sprite::start();
}

void Star::update(double delta) {
    if (transform->position.y < -30.0f) {
        transform->position.y = Window::getHeight() + 10.0f;
        transform->position.x = Window::getWidth() * Random::getFloat();
    }

    transform->position.y -= speed * delta;

    Sprite::update(delta);
}
