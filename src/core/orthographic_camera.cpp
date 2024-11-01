#include "orthographic_camera.h"

namespace core {
OrthographicCamera::OrthographicCamera(glm::vec3 position, float left, float right, float bottom, float top, float near, float far)
    : position(position), left(left), right(right), bottom(bottom), top(top), near(near), far(far) {
    setPosition(position);
    updateProjection(left, right, bottom, top, near, far);
}

void OrthographicCamera::updateProjection(float left, float right, float bottom, float top, float near, float far) {
    projection = glm::ortho(left, right, bottom, top, near, far);
}

}  // namespace core
