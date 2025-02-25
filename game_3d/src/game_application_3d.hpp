#ifndef GAME_APPLICATION_3D_HPP
#define GAME_APPLICATION_3D_HPP

#include "application.hpp"

class GameApplication3D : public Application {
   public:
    GameApplication3D();
    ~GameApplication3D();

    void init() override;
    
    using Application::run;
};

#endif
