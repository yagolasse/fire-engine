#include "ship.hpp"

#include <iostream>

#include "input.hpp"
#include "quad.hpp"
#include "window.hpp"

void Ship::start() {
    currentSprite = 24;

    transform->position.x = Window::getWidth() / 2.0f;
    transform->position.y = Window::getHeight() / 2.0f;

    Sprite::start();
}

void Ship::update(double delta) {
    glm::vec2 velocity{0, 0};

    if (Input::isKeyPressed(Input::Key::A)) {
        transform->rotationDegrees += rotationSpeed * delta;
    }

    if (Input::isKeyPressed(Input::Key::D)) {
        transform->rotationDegrees -= rotationSpeed * delta;
    }

    if (Input::isKeyPressed(Input::Key::W)) {
        float rad = glm::radians(transform->rotationDegrees - 90.0f);
        velocity.x -= glm::cos(rad);
        velocity.y -= glm::sin(rad);
    }

    if (Input::isKeyPressed(Input::Key::S)) {
        float rad = glm::radians(transform->rotationDegrees - 90.0f);
        velocity.x += glm::cos(rad);
        velocity.y += glm::sin(rad);
    }

    if (glm::length(velocity) != 0.0f) {
        transform->position += velocity * speed * (float)delta;
    }

    Sprite::update(delta);
}

bool Ship::onKeyEvent(Input::Key key, Input::KeyEventType type) {
    // if (key == Input::Key::F) {
    //     transform->rotationDegrees += 15.0f;
    //     return true;
    // }

    return false;
}
