#include "camera.hpp"

#include <gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) {
    setPosition(position);
}

void Camera::setPosition(glm::vec3 newPosition) {
    if (position == newPosition) return;

    position = newPosition;
    view = glm::lookAt(newPosition, cameraFront + newPosition, cameraUp);
}

void Camera::update(double delta) {
}

void Camera::updateProjection(PerspectiveData newPerspective) {
    perspective = newPerspective;

    projection = glm::perspective(
        newPerspective.fieldOfViewRadians, 
        newPerspective.aspectRatio, 
        newPerspective.nearClip, 
        newPerspective.farClip
    );
}

void Camera::updateProjection(OrthographicData newOrthographic) {
    orthographic = newOrthographic;

    projection = glm::ortho(
        newOrthographic.left, 
        newOrthographic.right, 
        newOrthographic.bottom, 
        newOrthographic.top, 
        newOrthographic.nearZ, 
        newOrthographic.farZ
    );
}
