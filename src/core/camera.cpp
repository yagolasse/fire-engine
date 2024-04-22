#include "camera.h"

#include <gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float fovRadians, float aspectRatio, float nearClip, float farClip) {
    setPosition(position);
    updateProjection(fovRadians, aspectRatio, nearClip, farClip);
}

Camera::~Camera() {
}

void Camera::setPosition(glm::vec3 newPosition) {
    position = newPosition;

    glm::vec3 target(0.0f, 0.0f, 0.0f);
    glm::vec3 direction = glm::normalize(position - target);

    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(up, direction));

    glm::vec3 cameraUp = glm::cross(direction, right);

    view = glm::lookAt(position, target, cameraUp);
}

void Camera::updateProjection(float fovRadians, float aspectRatio, float nearClip, float farClip) {
    this->fieldOfViewRadians = fovRadians;
    this->aspectRatio = aspectRatio;
    this->nearClip = nearClip;
    this->farClip = farClip;    

    projection = glm::perspective(fieldOfViewRadians, aspectRatio, nearClip, farClip);
}
