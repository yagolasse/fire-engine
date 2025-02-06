#pragma once

#include "scene.h"

class GameScene : public Scene {
   public:
    using Scene::Scene;

    void onStart() override;
    void onUpdate(double deltaTime) override;
};
