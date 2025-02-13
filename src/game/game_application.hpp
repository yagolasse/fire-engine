#ifndef GAME_APPLICATION_HPP
#define GAME_APPLICATION_HPP

#include "application.hpp"

class GameApplication : public Application {
   public:
    void init() override;
    void run() override;
};

#endif
