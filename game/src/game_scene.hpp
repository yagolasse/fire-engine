#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "scene.hpp"

class GameScene : public Scene {
   public:
    GameScene();

    void start() override;
    void update(double deltaTime) override;
    void render() override;
};

#endif
