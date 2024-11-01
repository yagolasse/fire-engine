#include "orthographic_camera.h"

OrthographicCamera::OrthographicCamera(glm::vec3 position, float left, float right, float bottom, float top, float nearZ, float farZ)
    : position(position), left(left), right(right), bottom(bottom), top(top), near(nearZ), far(farZ) {
    setPosition(position);
    updateProjection(left, right, bottom, top, nearZ, farZ);
}

void OrthographicCamera::updateProjection(float left, float right, float bottom, float top, float nearZ, float farZ) {
    projection = glm::ortho(left, right, bottom, top, nearZ, farZ);
}
