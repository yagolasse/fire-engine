#include "bullet.hpp"

#include <iostream>

#include "quad.hpp"
#include "scene.hpp"
#include "scene_manager.hpp"
#include "window.hpp"

Bullet::Bullet() {
    setTexture("simpleSpace_tilesheet.png");
    setTileSize(64, 64);
}

void Bullet::start() {
    currentSprite = 23;

    transform->scale = glm::vec2(0.4f);

    Sprite::start();
}

void Bullet::update(double delta) {
    if (transform->position.y > Window::getHeight() || transform->position.y < 0
    || transform->position.x > Window::getWidth() || transform->position.x < 0) {
        queueDeletion();
        return;
    }

    transform->position += direction * speed * (float)delta;

    Sprite::update(delta);
}
