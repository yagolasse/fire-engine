#pragma once

#include "scene.h"

class GameScene : public Scene {
   public:
    using Scene::Scene;

    void start() override;
    void update(double deltaTime) override;
    void render() override;
};
