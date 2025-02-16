#ifndef CAMERA_HPP
#define CAMERA_HPP

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
    Camera(glm::vec3 position, float left, float right, float top, float bottom, float near, float far);
    ~Camera();

    void setPosition(glm::vec3 newPosition);
    void updatePerspective(float fovRadians, float aspectRatio, float nearClip, float farClip);
    void updateOrthographic(float left, float right, float bottom, float top, float near, float far);

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

#endif
