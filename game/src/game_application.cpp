#include "game_application.hpp"

#include "batch_renderer.hpp"
#include "game_scene.hpp"
#include "scene_manager.hpp"

GameApplication::GameApplication() {
    BatchRenderer::getInstance()->init();
}

GameApplication::~GameApplication() {
    BatchRenderer::disposeInstance();
}

void GameApplication::init() {
    Application::init();

    SceneManager::getInstance()->replaceScene(new GameScene());
}
