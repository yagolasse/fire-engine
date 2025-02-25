#ifndef GAME_SCENE_3D_HPP
#define GAME_SCENE_3D_HPP

#include "scene.hpp"

class Mesh;

class VoxelGameScene : public Scene {
   private:
    Mesh* mesh;

   public:
    VoxelGameScene();
    ~VoxelGameScene();

    void start() override;
    void update(double deltaTime) override;
    void render() override;
};

#endif
