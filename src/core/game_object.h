#pragma once

struct Transform;

#include "input.h"

class GameObject {
   public:
    Transform* transform;

    GameObject();
    virtual ~GameObject();

    virtual void start() = 0;
    virtual void update(double delta) = 0;

    // virtual void onKeyPressed(Input::Key key) = 0;
};
