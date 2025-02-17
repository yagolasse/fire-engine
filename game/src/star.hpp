#ifndef STAR_HPP
#define STAR_HPP

#include "sprite.hpp"

class Star : public Sprite {
   private:
    const float baseSpeed = 100;
    float speed;

   public:
    Star();

    void start() override;
    void update(double delta) override;
};

#endif
