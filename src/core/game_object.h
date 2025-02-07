#pragma once

struct Transform;

#include "input.h"

class GameObject {
   private:
    int id;
    static long count;

   public:
    Transform* transform;

    GameObject();
    virtual ~GameObject();

    virtual void start() = 0;
    virtual void update(double delta) = 0;

    bool operator ==(GameObject& other);

    // virtual void onKeyPressed(Input::Key key) = 0;
};
