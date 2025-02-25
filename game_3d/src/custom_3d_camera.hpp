#ifndef CUSTOM_3D_CAMERA_HPP
#define CUSTOM_3D_CAMERA_HPP

#include "camera.hpp"

class Custom3DCamera : public Camera {
   public:
    using Camera::Camera;

    void update(double delta) override;
};

#endif
