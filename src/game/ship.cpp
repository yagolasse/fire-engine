#include "ship.h"

#include "input.h"
#include "quad.h"
#include "window.h"

void Ship::start() {
    transform->position.x = Window::getWidth() / 2.0f + 32.0f;
    transform->position.y = Window::getHeight() / 2.0f + 32.0f;

    Sprite::start();
}

void Ship::update(double delta) {
    if (Input::isKeyPressed(Input::Key::W)) {
        transform->position.y += speed * delta;
    }

    if (Input::isKeyPressed(Input::Key::S)) {
        transform->position.y -= speed * delta;
    }

    if (Input::isKeyPressed(Input::Key::A)) {
        transform->position.x -= speed * delta;
    }

    if (Input::isKeyPressed(Input::Key::D)) {
        transform->position.x += speed * delta;
    }

    Sprite::update(delta);
}
