#pragma once

#include <memory>

#include "asset_loader.h"
#include "batch_renderer.h"
#include "window.h"

class Application {
   private:
    std::unique_ptr<Window> window;
    std::unique_ptr<AssetLoader> assetLoader;
    std::shared_ptr<BatchRenderer> batchRenderer;

   public:
    Application();

    void run();
};
