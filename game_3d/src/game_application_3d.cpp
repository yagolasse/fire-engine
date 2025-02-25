#include "game_application_3d.hpp"

#include "batch_renderer.hpp"
#include "game_scene_3d.hpp"
#include "scene_manager.hpp"

GameApplication3D::GameApplication3D() {
}

GameApplication3D::~GameApplication3D() {
}

void GameApplication3D::init() {
    Application::init();

    SceneManager::getInstance()->replaceScene(new VoxelGameScene());
}
