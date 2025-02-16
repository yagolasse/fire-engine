#include "ship.hpp"

#include <iostream>
#include <memory>

#include "bullet.hpp"
#include "input.hpp"
#include "quad.hpp"
#include "scene.hpp"
#include "scene_manager.hpp"
#include "texture_region.hpp"
#include "texture_storage.hpp"
#include "window.hpp"

Ship::Ship() : Sprite() {
    textureData = TextureStorage::getInstance()->loadTexture("simpleSpace_tilesheet.png");
    textureRegion = new TextureRegion(textureData, 64, 64);
}

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

    shootTime += delta;

    Sprite::update(delta);
}

bool Ship::onKeyEvent(Input::Key key, Input::KeyEventType type) {
    if (key == Input::Key::F && shootTime > shootTimeout) {
        std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();

        float rad = glm::radians(transform->rotationDegrees + 90);

        glm::vec2 direction{glm::cos(rad), glm::sin(rad)};

        bullet->direction = direction;
        bullet->transform->position = transform->position + direction * 28.0f;

        SceneManager::getInstance()->getCurrentScene()->addObject(bullet);

        shootTime = 0.0f;

        return true;
    }

    return false;
}
