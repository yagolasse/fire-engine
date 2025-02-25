#include "game_scene_3d.hpp"

#include <glm.hpp>
#include <memory>

#include "custom_3d_camera.hpp"
#include "game_object.hpp"
#include "mesh.hpp"
#include "texture_data.hpp"
#include "texture_storage.hpp"

VoxelGameScene::VoxelGameScene() {
    camera = new Custom3DCamera(glm::vec3{0.0f,0.0f,3.0f});
    camera->updateProjection(PerspectiveData{glm::radians(70.0f), 1280.0f / 720.0f, 0.1f, 1000.0f});

    mesh = new Mesh();
}

VoxelGameScene::~VoxelGameScene() {
    delete mesh;
}

void VoxelGameScene::start() {
    mesh->init();

    Scene::start();
}

void VoxelGameScene::update(double deltaTime) {
    Scene::update(deltaTime);
}

void VoxelGameScene::render() {
    mesh->draw(camera);

    Scene::render();
}
