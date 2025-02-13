#ifndef SCENE_HPP
#define SCENE_HPP

#include "input.hpp"

#include <memory>
#include <vector>

class GameObject;
class BatchRenderer;
class OrthographicCamera;
class TextureStorage;

class Scene {
   protected:
    std::vector<GameObject*> gameObjects;
    std::shared_ptr<BatchRenderer> renderer;
    std::shared_ptr<OrthographicCamera> camera;
    std::shared_ptr<TextureStorage> textureStorage;

   public:
    Scene(std::shared_ptr<BatchRenderer> renderer, std::shared_ptr<TextureStorage> textureStorage);
    ~Scene();

    virtual void onKeyEvent(Input::Key key, Input::KeyEventType type);
    virtual void start();
    virtual void update(double deltaTime);
    virtual void render();
};

#endif
