#include "game_application.hpp"

#include "game_scene.hpp"
#include "scene_manager.hpp"

void GameApplication::init() {
    Application::init();

    // SceneManager::getInstance()->replaceScene(new GameScene());
}

void GameApplication::run() {
    Application::run();
}
