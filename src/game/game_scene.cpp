#include "game_scene.h"

#include "game_object.h"
#include "sprite.h"
#include "texture_storage.h"

void GameScene::onStart() {
    Scene::onStart();

    TextureData* textureData = textureStorage->loadTexture("../resources/simpleSpace_tilesheet.png");

    gameObjects.push_back(
        new Sprite(renderer, textureData, 64, 64)
    );
}

void GameScene::onUpdate(double deltaTime) {
    Scene::onUpdate(deltaTime);
}
