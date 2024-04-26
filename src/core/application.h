#pragma once

#include <memory>

#include "window.h"

class Application {
   private:
    float frameTime;
    float previousFrameTime;
    std::unique_ptr<Window> window;

   public:
    Application();
};
