#include "game_object.h"

#include "quad.h"

GameObject::GameObject() : transform(new Transform()) {
}

GameObject::~GameObject() {
    delete transform;
}
