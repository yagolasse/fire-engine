#pragma once

#include <memory>

class Scene;
class Window;
class BatchRenderer;
class TextureStorage;

class Application {
   private:
    Window* window;
    
   protected:
    std::shared_ptr<BatchRenderer> batchRenderer;
    std::shared_ptr<TextureStorage> textureStorage;

   public:
    Application();
    virtual ~Application();

    virtual void init();
    virtual void run();
};
