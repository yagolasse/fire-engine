#include "custom_3d_camera.hpp"

#include <glm.hpp>

#include "input.hpp"

void Custom3DCamera::update(double delta) {
    const float speed = 30;
    glm::vec3 movement(0.0f);

    if (Input::isKeyPressed(Input::Key::A)) {
        movement.x = -1;
    }

    if (Input::isKeyPressed(Input::Key::D)) {
        movement.x = 1;
    }

    if (Input::isKeyPressed(Input::Key::W)) {
        movement.y = 1;
    }

    if (Input::isKeyPressed(Input::Key::S)) {
        movement.y = -1;
    }

    setPosition(position + movement * speed * (float)delta);
}
