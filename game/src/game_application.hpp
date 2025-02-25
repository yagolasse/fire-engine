#ifndef GAME_APPLICATION_HPP
#define GAME_APPLICATION_HPP

#include "application.hpp"

class GameApplication : public Application {
   public:
    GameApplication();
    ~GameApplication();

    void init() override;
    
    using Application::run;
};

#endif
