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

    transform->scale *= 0.3f * Random::getFloat();

    Sprite::start();
}

void Star::update(double delta) {
    Sprite::update(delta);
}
