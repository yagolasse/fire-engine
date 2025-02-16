#include "orthographic_camera.hpp"

OrthographicCamera::OrthographicCamera(glm::vec3 position, float left, float right, float bottom, float top, float nearZ, float farZ)
    : position(position), left(left), right(right), bottom(bottom), top(top), near(nearZ), far(farZ) {
    setPosition(position);
    updateProjection(left, right, bottom, top, nearZ, farZ);
}

void OrthographicCamera::updateProjection(float left, float right, float bottom, float top, float nearZ, float farZ) {
    projection = glm::ortho(left, right, bottom, top, nearZ, farZ);
}

void OrthographicCamera::setPosition(glm::vec3 newPosition) {
    position = newPosition;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    view = glm::lookAt(
        glm::vec3(position.x, position.y, 20.0f),
        cameraFront + glm::vec3(position.x, position.y, 0.0f),
        cameraUp
    );
}
