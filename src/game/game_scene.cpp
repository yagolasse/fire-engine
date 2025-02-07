#include "game_scene.h"

#include "game_object.h"
#include "ship.h"
#include "star.h"
#include "texture_data.h"
#include "texture_storage.h"

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

    Scene::start();
}

void GameScene::update(double deltaTime) {
    Scene::update(deltaTime);
}

void GameScene::render() {
    Scene::render();
}
