#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "input.hpp"

class GameObject;
class BatchRenderer;
class Camera;
class TextureStorage;

class Scene {
   protected:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    
    std::shared_ptr<Camera> camera;

   public:
    Scene();
    ~Scene();

    virtual void start();
    virtual void update(double deltaTime);
    virtual void render();

    virtual void onKeyEvent(Input::Key key, Input::KeyEventType type);

    virtual void addObject(std::shared_ptr<GameObject> gameObject);
};

#endif
