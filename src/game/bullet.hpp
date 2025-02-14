#ifndef BULLET_HPP
#define BULLET_HPP

#include <glm.hpp>

#include "sprite.hpp"

class Bullet : public Sprite {
   private:
    const float speed = 500.0f;

   public:
    glm::vec2 direction;

    Bullet();

    void start() override;
    void update(double delta) override;
};

#endif