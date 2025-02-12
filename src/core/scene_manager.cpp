#include "scene_manager.h"

#include "assertion.h"
#include "scene.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::getInstance() {
    if (SceneManager::instance == nullptr) {
        instance = new SceneManager();
    }
    return instance;
}

void SceneManager::disposeInstance() {
    delete instance;
}

Scene* SceneManager::getCurrentScene() {
    return currentScene;
}

SceneManager::SceneManager() {
    currentScene = nullptr;
}

SceneManager::~SceneManager() {
    if (currentScene != nullptr) {
        delete currentScene;
    }
}

void SceneManager::replaceScene(Scene* newScene) {
    if (currentScene != nullptr) {
        delete currentScene;
    }

    currentScene = newScene;
}

void SceneManager::startScene() {
    ASSERT_MSG(currentScene, "Current scene must not be null");

    currentScene->start();
}

void SceneManager::runSceneUpdate(double delta) {
    ASSERT_MSG(currentScene, "Current scene must not be null");

    currentScene->update(delta);
}

void SceneManager::runSceneRender() {
    ASSERT_MSG(currentScene, "Current scene must not be null");

    currentScene->render();
}
