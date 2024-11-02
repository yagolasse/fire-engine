#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

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
    OrthographicCamera(glm::vec3 position, float left, float right, float bottom, float top, float nearZ, float farZ);

    void updateProjection(float left, float right, float bottom, float top,  float near, float far);

    void setPosition(glm::vec3 newPosition);

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
