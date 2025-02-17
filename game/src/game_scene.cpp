#include "game_scene.hpp"

#include <memory>

#include "bullet.hpp"
#include "game_object.hpp"
#include "ship.hpp"
#include "star.hpp"
#include "texture_data.hpp"
#include "texture_storage.hpp"

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
}
