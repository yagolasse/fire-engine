#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>

#include "input.hpp"

struct Transform;

class GameObject {
   private:
    static long count;

   protected:
    int id;
    bool markedForDeletion = false;

   public:
    Transform* transform;

    GameObject();
    virtual ~GameObject();

    virtual void start() = 0;
    virtual void update(double delta) = 0;
    virtual void render();
    virtual bool onKeyEvent(Input::Key key, Input::KeyEventType type);

    virtual void queueDeletion();
    virtual bool isDeletionQueued();

    bool operator==(GameObject& other);
};

#endif
