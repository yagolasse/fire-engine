#include "bullet.hpp"

#include <iostream>

#include "quad.hpp"
#include "scene.hpp"
#include "scene_manager.hpp"
#include "window.hpp"

void Bullet::start() {
    currentSprite = 41;

    transform->position.x = Window::getWidth() / 2.0f;
    transform->position.y = Window::getHeight() / 2.0f;

    transform->scale = glm::vec2(0.4f);
    Sprite::start();
}

void Bullet::update(double delta) {
    if (transform->position.x > Window::getWidth() * 0.75f) {
        queueDeletion();
        return;
    }

    std::cout << transform->position.x << std::endl;

    transform->position.x += 30.0f * delta;

    Sprite::update(delta);
}
