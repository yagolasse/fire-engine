#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace core {
class OrthographicCamera {
   private:
    float left;
    float right;
    float top;
    float bottom;
    float near;
    float far;

    bool isDirty;

    glm::vec3 position;
    glm::mat4 view;
    glm::mat4 projection;
   public:
    OrthographicCamera(glm::vec3 position, float left, float right, float bottom, float top, float near, float far);

    void updateProjection(float left, float right, float bottom, float top,  float near, float far);

    inline void setPosition(glm::vec3 newPosition) {
        position = newPosition;
        view = glm::translate(glm::mat4(1.0f), position);
    }

    inline const glm::vec3 getPosition() const {
        return position;
    }

    inline const glm::mat4 getProjection() const {
        return projection;
    }

    inline const glm::mat4 getView() const {
        return view;
    }
};
}  // namespace core
