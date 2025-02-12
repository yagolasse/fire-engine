#include "game_object.h"

#include "input.h"
#include "quad.h"

long GameObject::count = 0;

GameObject::GameObject() : transform(new Transform()) {
    id = count++;
}

GameObject::~GameObject() {
    delete transform;
}

bool GameObject::onKeyEvent(Input::Key key, Input::KeyEventType type) {
    return false;
}

bool GameObject::operator==(GameObject& other) {
    return id == other.id;
}
