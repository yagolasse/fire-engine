#include "scene.hpp"

#include <vector>

#include "batch_renderer.hpp"
#include "camera.hpp"
#include "game_object.hpp"
#include "sprite.hpp"
#include "texture_data.hpp"
#include "texture_storage.hpp"

Scene::Scene() {
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

    gameObject->start();
}

void Scene::start() {
    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        gameObject->start();
    }
}

void Scene::update(double deltaTime) {
#ifdef __linux__
    for (auto it = gameObjects.begin(); it != gameObjects.end(); /* Nothing */) {
        if ((*it)->isDeletionQueued()) {
            it = gameObjects.erase(it);
        } else {
            ++it;
        }
    }
#else
    gameObjects.erase(
        std::remove_if(
            gameObjects.begin(), 
            gameObjects.end(),
            [](std::shared_ptr<GameObject> gameObject) { 
                return gameObject->isDeletionQueued(); 
            }),
        gameObjects.end());
#endif

    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        gameObject->update(deltaTime);
    }
}

void Scene::render() {
    for (std::shared_ptr<GameObject> gameObject : gameObjects) {
        gameObject->render();
    }
}
