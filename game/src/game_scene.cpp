#include "game_scene.hpp"

#include <gtc/type_ptr.hpp>
#include <memory>

#include "batch_renderer.hpp"
#include "bullet.hpp"
#include "camera.hpp"
#include "game_object.hpp"
#include "ship.hpp"
#include "star.hpp"
#include "texture_data.hpp"
#include "texture_storage.hpp"

GameScene::GameScene() {
    camera = std::make_shared<Camera>(glm::vec3{0.0f, 0.0f, 3.0f});
    camera->update(OrthographicData{0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 1000.0f});
}

void GameScene::start() {
    for (int i = 0; i < 100; i++) {
        gameObjects.push_back(std::make_shared<Star>());
    }

    gameObjects.push_back(std::make_shared<Ship>());

    Scene::start();
}

void GameScene::update(double deltaTime) {
    Scene::update(deltaTime);
}

void GameScene::render() {
    Scene::render();

    BatchRenderer::getInstance()->draw(glm::value_ptr(camera->getView()), glm::value_ptr(camera->getProjection()));
}
