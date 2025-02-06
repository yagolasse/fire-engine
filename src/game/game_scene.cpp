#include "game_scene.h"

#include "game_object.h"
#include "ship.h"
#include "star.h"
#include "texture_data.h"
#include "texture_storage.h"

void GameScene::onStart() {
    TextureData* textureData = textureStorage->loadTexture("../resources/simpleSpace_tilesheet.png");

    gameObjects.push_back(
        new Ship(renderer, textureData, 64, 64)
    );

    for (int i = 0; i < 100; i++) {
        gameObjects.push_back(
            new Star(renderer, textureData, 64, 64)
        );      
    }

    Scene::onStart();
}

void GameScene::onUpdate(double deltaTime) {
    Scene::onUpdate(deltaTime);
}
