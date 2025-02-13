#include "game_scene.hpp"

#include "bullet.hpp"
#include "game_object.hpp"
#include "ship.hpp"
#include "star.hpp"
#include "texture_data.hpp"
#include "texture_storage.hpp"

void GameScene::start() {
    TextureData* textureData = textureStorage->loadTexture("../resources/simpleSpace_tilesheet.png");

    for (int i = 0; i < 100; i++) {
        gameObjects.push_back(
            new Star(renderer, textureData, 64, 64)
        );      
    }
    
    gameObjects.push_back(
        new Ship(renderer, textureData, 64, 64)
    );

    gameObjects.push_back(
        new Bullet(renderer, textureData, 64, 64)
    );

    Scene::start();
}

void GameScene::update(double deltaTime) {
    Scene::update(deltaTime);
}

void GameScene::render() {
    Scene::render();
}
