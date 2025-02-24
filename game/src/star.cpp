#include "star.hpp"

#include <iostream>

#include "assertion.hpp"
#include "random.hpp"
#include "quad.hpp"
#include "window.hpp"

Star::Star() {
    setTexture("simpleSpace_tilesheet.png");
    setTileSize(64, 64);
}

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
