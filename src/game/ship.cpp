#include "ship.h"

#include <iostream>

#include "input.h"
#include "quad.h"
#include "window.h"

void Ship::start() {
    currentSprite = 24;

    transform->position.x = Window::getWidth() / 2.0f;
    transform->position.y = Window::getHeight() / 2.0f;

    Sprite::start();
}

void Ship::update(double delta) {
    glm::vec2 velocity{0, 0};

    if (Input::isKeyPressed(Input::Key::W)) {
        velocity.y += 1;
    }

    if (Input::isKeyPressed(Input::Key::S)) {
        velocity.y -= 1;
    }

    if (Input::isKeyPressed(Input::Key::A)) {
        velocity.x -= 1;
    }

    if (Input::isKeyPressed(Input::Key::D)) {
        velocity.x += 1;
    }

    if (glm::length(velocity) != 0.0f) {
        transform->position += glm::normalize(velocity) * speed * (float)delta;
    }

    Sprite::update(delta);
}

bool Ship::onKeyEvent(Input::Key key, Input::KeyEventType type) {
    if (key == Input::Key::F) {
        transform->rotationDegrees += 15.0f;
        return true;
    }

    return false;
}
