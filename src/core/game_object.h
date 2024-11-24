#pragma once

#include "quad.h"
#include "texture.h"

class GameObject {
   public:
    Transform transform;

    GameObject();

    void start();
    void update(double delta);
};

class Sprite : public GameObject {
   public:
    Texture texture;
};
