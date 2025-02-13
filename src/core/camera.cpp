#include "camera.hpp"

#include <gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float fovRadians, float aspectRatio, float nearClip, float farClip) {
    setPosition(position);
    updatePerspective(fovRadians, aspectRatio, nearClip, farClip);
}

Camera::Camera(glm::vec3 position, float left, float right, float top, float bottom, float near, float far) {
    setPosition(position);
    updateOrthographic(left, right, top, bottom, near, far);
}

Camera::~Camera() {
}

void Camera::setPosition(glm::vec3 newPosition) {
    position = newPosition;

    // glm::vec3 target(0.0f, 0.0f, 0.0f);
    // glm::vec3 direction = glm::normalize(position - target);

    // glm::vec3 up(0.0f, 1.0f, 0.0f);
    // glm::vec3 right = glm::normalize(glm::cross(up, direction));

    // glm::vec3 cameraUp = glm::cross(direction, right);

    // view = glm::lookAt(position, target, cameraUp);
    view = glm::mat4(1.0f);
    view = glm::translate(view, newPosition);
}

void Camera::updatePerspective(float fovRadians, float aspectRatio, float nearClip, float farClip) {
    this->fieldOfViewRadians = fovRadians;
    this->aspectRatio = aspectRatio;
    this->nearClip = nearClip;
    this->farClip = farClip;    

    projection = glm::perspective(fieldOfViewRadians, aspectRatio, nearClip, farClip);
}

void Camera::updateOrthographic(float left, float right, float bottom, float top, float near, float far) {
    projection = glm::ortho(left, right, bottom, top, near, far);
}
