#pragma once

#include <memory>

#include "window.h"
#include "batch_renderer.h"

class Application {
   private:
    std::unique_ptr<Window> window;
    std::unique_ptr<BatchRenderer> batchRenderer;

   public:
    Application();

    void run();
};
