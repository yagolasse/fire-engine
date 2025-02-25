#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm.hpp>

struct PerspectiveData {
    float fieldOfViewRadians;
    float aspectRatio;
    float nearClip;
    float farClip;
};

struct OrthographicData {
    float left;
    float right;
    float bottom;
    float top;
    float nearZ;
    float farZ;
};

class Camera {
   private:
    PerspectiveData perspective;
    OrthographicData orthographic;

    glm::vec3 position;
    glm::mat4 view;
    glm::mat4 projection;

    const glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

   public:
    Camera(glm::vec3 position);

    void setPosition(glm::vec3 newPosition);

    void update(PerspectiveData newPerspective);
    void update(OrthographicData newOrthographic);

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
