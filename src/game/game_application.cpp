#include <game_application.h>

#include "game_scene.h"

void GameApplication::init() {
    Application::init();

    scene = new GameScene(batchRenderer, textureStorage);
}

void GameApplication::run() {
    Application::run();
}
