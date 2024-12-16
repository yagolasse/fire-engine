#pragma once

#include <camera.h>

#include <vector>

#include "batch_renderer.h"
#include "game_object.h"
#include "orthographic_camera.h"
#include "texture_storage.h"

class Scene {
   private:
    std::vector<GameObject *> gameObjects;
    std::shared_ptr<BatchRenderer> renderer;
    std::shared_ptr<OrthographicCamera> camera;
    std::shared_ptr<TextureStorage> textureStorage;

   public:
    Scene(std::shared_ptr<BatchRenderer> renderer, std::shared_ptr<TextureStorage> textureStorage);
    ~Scene();
    void onStart();
    void onUpdate(double deltaTime);
};
