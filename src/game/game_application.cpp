#include <game_application.h>

#include "game_scene.h"
#include "scene_manager.h"

void GameApplication::init() {
    Application::init();

    SceneManager::getInstance()->replaceScene(new GameScene(batchRenderer, textureStorage));
}

void GameApplication::run() {
    Application::run();
}
