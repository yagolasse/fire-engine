#pragma once

#include <glm.hpp>

class Camera {
   private:
    glm::vec3 position;
    glm::mat4 view;

   public:
    Camera(glm::vec3 position);
    ~Camera();

    void setPosition(glm::vec3 newPosition);

    inline const glm::mat4 getView() const {
        return view;
    }
};
