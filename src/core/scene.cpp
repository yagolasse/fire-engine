#include "scene.h"

#include <gtc/type_ptr.hpp>

#include "batch_renderer.h"
#include "game_object.h"
#include "orthographic_camera.h"
#include "sprite.h"
#include "texture_storage.h"

Scene::Scene(std::shared_ptr<BatchRenderer> renderer, std::shared_ptr<TextureStorage> textureStorage)
    : renderer(renderer), textureStorage(textureStorage) {
    camera = std::make_shared<OrthographicCamera>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 1000.0f);
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

    renderer->draw(glm::value_ptr(camera->getView()), glm::value_ptr(camera->getProjection()));
}
