#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>

class Window;

class Application {
   private:
    Window* window;
    
   public:
    Application();
    virtual ~Application();

    virtual void init();
    virtual void run();
};

#endif
