#include "camera.h"

#include <gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) {
    setPosition(position);
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
