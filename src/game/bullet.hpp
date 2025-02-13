#ifndef BULLET_HPP
#define BULLET_HPP

#include "sprite.hpp"

class Bullet : public Sprite {
   public:
    using Sprite::Sprite;

    void start() override;
    void update(double delta) override;

   private:
};

#endif