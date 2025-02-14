#include "scene.hpp"

#include <gtc/type_ptr.hpp>

#include "batch_renderer.hpp"
#include "game_object.hpp"
#include "orthographic_camera.hpp"
#include "sprite.hpp"
#include "texture_data.hpp"
#include "texture_storage.hpp"

Scene::Scene() {
    camera = std::make_shared<OrthographicCamera>(glm::vec3{0.0f, 0.0f, 3.0f}, 0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 1000.0f);
}

Scene::~Scene() {
}

void Scene::onKeyEvent(Input::Key key, Input::KeyEventType type) {
    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        if (gameObject->onKeyEvent(key, type)) {
            break;
        }
    }
}

void Scene::addObject(std::shared_ptr<GameObject> gameObject) {
    gameObjects.push_back(gameObject);
}

void Scene::start() {
    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        gameObject->start();
    }
}

void Scene::update(double deltaTime) {
    gameObjects.erase(
        std::remove_if(
        gameObjects.begin(), gameObjects.end(), [](std::shared_ptr<GameObject> gameObjects) { 
            return gameObjects->isDeletionQueued(); 
        }),
        gameObjects.end()
    );

    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        gameObject->update(deltaTime);
    }
}

void Scene::render() {
    BatchRenderer::getInstance()->draw(glm::value_ptr(camera->getView()), glm::value_ptr(camera->getProjection()));
}
