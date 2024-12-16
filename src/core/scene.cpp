#include "scene.h"

#include "sprite.h"

Scene::Scene(std::shared_ptr<BatchRenderer> renderer, std::shared_ptr<TextureStorage> textureStorage)
    : renderer(renderer) {
    camera =
        std::make_shared<OrthographicCamera>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 1000.0f);

    gameObjects.push_back(
        new Sprite(renderer, textureStorage->loadTexture("../resources/simpleSpace_tilesheet.png"), 64, 64));
}

Scene::~Scene() {
    for (GameObject* gameObject : gameObjects) {
        delete gameObject;
    }
}

void Scene::onStart() {
    for (GameObject* gameObject : gameObjects) {
        gameObject->start();
    }
}

void Scene::onUpdate(double deltaTime) {
    for (GameObject* gameObject : gameObjects) {
        gameObject->update(deltaTime);
    }

    renderer->draw(camera);
}
