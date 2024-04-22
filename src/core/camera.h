#pragma once

#include <glm.hpp>

class Camera {
   private:
    float fieldOfViewRadians;
    float aspectRatio;
    float nearClip;
    float farClip;

    glm::vec3 position;
    glm::mat4 view;
    glm::mat4 projection;

   public:
    Camera(glm::vec3 position, float fovRadians, float aspectRatio, float nearClip, float farClip);
    ~Camera();

    void setPosition(glm::vec3 newPosition);
    void updateProjection(float fovRadians, float aspectRatio, float nearClip, float farClip);

    inline const glm::mat4 getProjection() const {
        return projection;
    }

    inline const glm::mat4 getView() const {
        return view;
    }
};
