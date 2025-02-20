#include "game_object.hpp"

#include "input.hpp"
#include "quad.hpp"

long GameObject::count = 0;

GameObject::GameObject() : transform(new Transform()) {
    id = count++;
}

GameObject::~GameObject() {
    delete transform;
}

void GameObject::render() {
}

bool GameObject::onKeyEvent(Input::Key key, Input::KeyEventType type) {
    return false;
}

void GameObject::queueDeletion() {
    markedForDeletion = true;
}

bool GameObject::isDeletionQueued() {
    return markedForDeletion;
}

bool GameObject::operator==(GameObject& other) {
    return id == other.id;
}
