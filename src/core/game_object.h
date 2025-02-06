#pragma once

struct Transform;

class GameObject {
   public:
    Transform* transform;

    GameObject();
    virtual ~GameObject();

    virtual void start() = 0;
    virtual void update(double delta) = 0;
};
