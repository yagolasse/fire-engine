#pragma once

#include <vector>

#include "input.h"

struct Transform;

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
    virtual bool onKeyEvent(Input::Key key, Input::KeyEventType type);

    bool operator==(GameObject& other);
};
