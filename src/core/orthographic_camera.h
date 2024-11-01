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

    inline void setPosition(glm::vec3 newPosition) {
        position = newPosition;
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        view = glm::lookAt(
            glm::vec3(position.x, position.y, 20.0f), 
            cameraFront + glm::vec3(position.x, position.y, 0.0f),
            cameraUp
        );
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
