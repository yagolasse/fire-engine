#pragma once

#include <memory>

#include "batch_renderer.h"
#include "texture_storage.h"
#include "window.h"

class Application {
   private:
    std::unique_ptr<Window> window;
    std::shared_ptr<BatchRenderer> batchRenderer;
    std::shared_ptr<TextureStorage> textureStorage;

   public:
    Application();

    void run();
};
